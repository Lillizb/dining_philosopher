/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:57:59 by ygao              #+#    #+#             */
/*   Updated: 2024/12/04 17:54:19 by ygao             ###   ########.fr       */
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
	bool	end;

	pthread_mutex_lock(&table->mutex);
	end = table->end_simulation;
	pthread_mutex_unlock(&table->mutex);
	return (end);
}

// void	free_fork(t_philo *philo, t_table *table)
// {
// 	int	first_fork;
// 	int	second_fork;
// 	int	tmp;

// 	first_fork = philo->id;
// 	second_fork = (philo->id + 1) % table->philo_sum;
// 	if (first_fork > second_fork)
// 	{
// 		tmp = first_fork;
// 		first_fork = second_fork;
// 		second_fork = tmp;
// 	}
// 	pthread_mutex_unlock(&philo->fork[first_fork].mutex);
// 	write_message(FREE_FIRST_FORK, philo);
// 	pthread_mutex_unlock(&philo->fork[second_fork].mutex);
// 	write_message(FREE_SECOND_FORK, philo);
// }

void	write_message(t_symbol	symbol, t_philo *philo)
{
	long		time;

	time = (get_microseconds() - philo->table->start_time) / 1000;
	pthread_mutex_lock(&philo->table->write_mutex);
	if (philo->table->end_simulation == true)
	{
		pthread_mutex_unlock(&philo->table->write_mutex);
		return ;
	}
	if (symbol == DIED)
		printf(R " %ld %d died\n"B, time, philo->id);
	else if (symbol == EATING && philo->table->end_simulation == false)
		printf(G " %ld %d is eating\n"B, time, philo->id);
	else if (symbol == SLEEPING)
		printf(Y " %ld %d is sleeping\n"B, time, philo->id);
	else if (symbol == TAKE_FIRST_FORK)
		printf(B " %ld %d has taken first fork\n", time, philo->id);
	else if (symbol == TAKE_SECOND_FORK)
		printf(" %ld %d has taken second fork\n", time, philo->id);
	else if (symbol == FREE_FIRST_FORK)
		printf("%d has freed first fork\n", philo->id);
	else if (symbol == FREE_SECOND_FORK)
		printf("%d has freed second fork\n", philo->id);
	else if (symbol == THINKING)
		printf(Y " %ld %d is thinking\n", time, philo->id);
	pthread_mutex_unlock(&philo->table->write_mutex);
}
