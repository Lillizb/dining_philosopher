/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:57:59 by ygao              #+#    #+#             */
/*   Updated: 2024/11/18 16:50:50 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	read_bool(pthread_mutex_t *mutex, bool *value)
{
	bool	result;

	pthread_mutex_lock(mutex);
	result = *value;
	pthread_mutex_unlock(mutex);
	return (result);
}

bool	end_simulation(t_table *table)
{
	bool	result;

	pthread_mutex_lock(&table->mutex);
	result = table->end_simulation;
	pthread_mutex_unlock(&table->mutex);
	return (result);
}

void	take_fork(t_philo *philo, t_table *table)
{
	int	first_fork;
	int	second_fork;
	int	tmp;

	first_fork = philo->id;
	second_fork = (philo->id + 1) % table->philo_sum;
	if (first_fork > second_fork)
	{
		tmp = first_fork;
		first_fork = second_fork;
		second_fork = tmp;
	}
	if (read_bool(&philo->table->mutex, &philo->table->end_simulation))
   	{
		pthread_mutex_unlock(&philo->fork[first_fork].mutex);
		return ;
	} 
	pthread_mutex_lock(&philo->fork[first_fork].mutex);
	pthread_mutex_lock(&philo->fork[second_fork].mutex);
	write_message(TAKE_FIRST_FORK, philo);
	write_message(TAKE_SECOND_FORK, philo);
}

void	free_fork(t_philo *philo, t_table *table)
{
	int	first_fork;
	int	second_fork;
	int	tmp;

	first_fork = philo->id;
	second_fork = (philo->id + 1) % table->philo_sum;
	if (first_fork > second_fork)
	{
		tmp = first_fork;
		first_fork = second_fork;
		second_fork = tmp;
	}
	pthread_mutex_unlock(&philo->fork[first_fork].mutex);
	pthread_mutex_unlock(&philo->fork[second_fork].mutex);
}

void	write_message(t_symbol	symbol, t_philo *philo)
{
	long		time;

//the value of time is 0 by compiling
	time = get_microseconds() - philo->table->start_time;
	pthread_mutex_lock(&philo->table->write_mutex);
	if (philo->table->end_simulation == true)
	{
		pthread_mutex_unlock(&philo->table->write_mutex);
		return ;
	}
	if (symbol == DIED)
		printf(R" %ld %d died\n"B, time, philo->id);
	else if (symbol == EATING && philo->table->end_simulation == false)
		printf(G" %ld %d is eating\n"B, time, philo->id);
	else if (symbol == SLEEPING)
		printf(B" %ld %d is sleeping\n"B, time, philo->id);
	else if (symbol == TAKE_FIRST_FORK)
		printf(" %ld %d has taken a fork\n", time, philo->id);
	else if (symbol == TAKE_SECOND_FORK)
		printf(" %ld %d has taken a fork\n", time, philo->id);
	else if (symbol == THINKING)
		printf(" %ld %d is thinking\n", time, philo->id);
	pthread_mutex_unlock(&philo->table->write_mutex);
}
