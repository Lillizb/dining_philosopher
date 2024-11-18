/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:57:59 by ygao              #+#    #+#             */
/*   Updated: 2024/11/18 14:00:18 by ygao             ###   ########.fr       */
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

long	get_time(void)
{
	struct timeval	tv;
	long			start;

	if (gettimeofday(&tv, NULL) != 0)
	{
		printf("Time of Day: Errpr!\n");
		return (-1);
	}
	start = tv.tv_sec * 1e3 + tv.tv_usec / 1e3;
	return (start);
}

void	write_message(t_symbol	symbol, t_philo *philo)
{
	long		time;

	time = get_time() - philo->table->start_time;
	pthread_mutex_lock(&philo->table->write_mutex);
	if (philo->table->end_simulation == true)
	{
		pthread_mutex_unlock(&philo->table->write_mutex);
		return ;
	}
	if (symbol == DIED)
		printf(R" %ld %d died\n"B, time, philo->id);
	else if (symbol == EATING)
		printf(G" %ld %d is eating\n"B, time, philo->id);
	else if (symbol == SLEEPING)
		printf(" %ld %d is sleeping\n", time, philo->id);
	else if (symbol == TAKE_FIRST_FORK)
		printf(" %ld %d has taken a fork\n", time, philo->id);
	else if (symbol == TAKE_SECOND_FORK)
		printf(" %ld %d has taken a fork\n", time, philo->id);
	else if (symbol == THINKING)
		printf(" %ld %d is thinking\n", time, philo->id);
	pthread_mutex_unlock(&philo->table->write_mutex);
}
