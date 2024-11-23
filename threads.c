/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:04:16 by ygao              #+#    #+#             */
/*   Updated: 2024/11/23 13:05:53 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_thread(t_table *table)   
{
	int	i;

	i = -1;
	if (table->philo->must_eat < -1 || table->philo_sum == 0)
		return ;
	if (table->philo_sum == 1)
		return (one_philo(table));
	while (++i < table->philo_sum)
	{
		printf("Creating thread %d\n", i);
		if (pthread_create(&table->philo[i].thread, NULL, 
				&routine, &table->philo[i]) != 0)
			error_exit(ALLOC_ERR_THREAD, table);
	}
	if (pthread_create(&table->monitor, NULL, &monitor, table) != 0)
		error_exit(ALLOC_ERR_THREAD, table);
	pthread_mutex_lock(&table->mutex);
	table->ready = true;
	table->start_time = get_microseconds();
	pthread_mutex_unlock(&table->mutex);
	join_threads(table);
	pthread_join(table->monitor, NULL);
}

void	*monitor(void *data)
{
	t_table	*table;
	int		i;
	long	time_gap_last_meal;

	table = (t_table *)data;
	while (!threads_all_running(table))
		 ;
	while (!end_simulation(table))
	{
		i = -1;
		while (++i < table->philo_sum)
		{
			pthread_mutex_lock(&table->philo[i].mutex);
			time_gap_last_meal = get_microseconds() 
					- table->philo[i].last_meal_time;
			if (!table->philo[i].eating && time_gap_last_meal >= table->time_to_die)
			{
				write_message(DIED, &table->philo[i]);
				pthread_mutex_unlock(&table->philo[i].mutex);
				pthread_mutex_lock(&table->mutex);
				table->end_simulation = true;
				pthread_mutex_unlock(&table->mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&table->philo[i].mutex);
		}
		ft_usleep(1000);
	}
	return (NULL);
}

void	join_threads(t_table *table)
{
	int	i;

	i = -1;
	while (table->philo_sum > ++i)
	{
		if (pthread_join(table->philo[i].thread, NULL))
			clean_and_exit(table);
		ft_usleep(1000);
	}
	if (pthread_join(table->monitor, NULL) != 0)
		clean_and_exit(table);
}
