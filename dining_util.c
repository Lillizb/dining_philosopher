/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:57:59 by ygao              #+#    #+#             */
/*   Updated: 2024/10/16 13:34:16 by ygao             ###   ########.fr       */
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
	if (philo->table->end_simulation)
		return ;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork[philo->id].mutex);
		pthread_mutex_lock(&philo->fork[(philo->id + 1) 
			% table->philo_sum].mutex);
	}
	else
	{
		pthread_mutex_lock(&philo->fork[philo->id].mutex);
		pthread_mutex_lock(&philo->fork[(philo->id - 1) 
			% table->philo_sum].mutex);
	}
}

void	free_fork(t_philo *philo, t_table *table)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->fork[philo->id].mutex);
		pthread_mutex_unlock(&philo->fork[(philo->id + 1) 
			% table->philo_sum].mutex);
	}
	else
	{
		pthread_mutex_unlock(&philo->fork[philo->id].mutex);
		pthread_mutex_unlock(&philo->fork[(philo->id - 1) 
			% table->philo_sum].mutex);
	}
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

void	write_message(char *s, t_philo *philo)
{
	long	time;

	time = get_time() - philo->table->start_time;
	pthread_mutex_lock(&philo->table->write_mutex);
	if (philo->table->end_simulation == true)
	{
		pthread_mutex_unlock(&philo->table->write_mutex);
		return ;
	}
	if (ft_strcmp("DIED", s) == 0)
		printf(R" %ld %d died\n"B, time, philo->id);
	else if (ft_strcmp("EATING", s) == 0)
		printf(G" %ld %d is eating\n"B, time, philo->id);
	else if (ft_strcmp("SLEEPING", s) == 0)
		printf(" %ld %d is sleeping\n", time, philo->id);
	else if (ft_strcmp("TAKE_FIRST_FORK", s) == 0)
		printf(" %ld %d has taken a fork\n", time, philo->id);
	else if (ft_strcmp("TAKE_SECOND_FORK", s) == 0)
		printf(" %ld %d has taken a fork\n", time, philo->id);
	else if (ft_strcmp("THINKING", s) == 0)
		printf(" %ld %d is thinking\n", time, philo->id);
	pthread_mutex_unlock(&philo->table->write_mutex);
}
