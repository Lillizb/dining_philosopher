/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:04:16 by ygao              #+#    #+#             */
/*   Updated: 2024/11/18 14:40:55 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_thread(t_table *table)
{
	int	i;

	i = -1;
	if (table->philo->must_eat > -1 || table->philo_sum == 0)
		return ;
	table->thread = malloc(sizeof(pthread_t) * table->philo_sum);
	if (table->thread == NULL)
		error_exit(MEMORY_ALLOCATION_ERROR, table);
	if (table->philo_sum == 1)
		return (one_philo(table));
	while (++i < table->philo_sum)
	{
		printf("Creating thread %d\n", i);
		if (pthread_create(&table->thread[i], NULL, 
				&routine, &table->philo[i]) != 0)
			error_exit(ALLOC_ERR_THREAD, table);
		pthread_mutex_lock(&table->mutex);
		if (i == table->philo_sum)
		{
			table->start_time = get_time();
			table->ready = true;
		}
		pthread_mutex_unlock(&table->mutex);
	}
	//table->monitor = malloc(sizeof(pthread_t));
	if (pthread_create(&table->monitor, NULL, &monitor, table) != 0)
		error_exit(ALLOC_ERR_THREAD, table);
	join_threads(table);
	free(table->thread);
}

void	*monitor(void *data)
{
	t_table	*table;
	int		i;
	long	time_gap_last_meal;

	table = (t_table *)data;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&table->mutex);
		while (i < table->philo_sum)
		{
			printf("minitoring philo %d\n", i);
			printf("table last_meal time %ld\n", table->philo[i].last_meal_time);
			time_gap_last_meal = get_time() - table->philo[i].last_meal_time;
			if (time_gap_last_meal > table->time_to_die)
			{
				printf("time_gap_last_meal %ld \n", time_gap_last_meal);
				table->philo[i].dead = 1;
				write_message(DIED, &table->philo[i]);
				table->end_simulation = true;
				pthread_mutex_unlock(&table->mutex);
				return (NULL);
			}
			i++;
		}
		if (table->end_simulation)
		{
			pthread_mutex_unlock(&table->mutex);
			break ;
		}
		pthread_mutex_unlock(&table->mutex);
		usleep(1000);
	}
	return (NULL);
}

void	join_threads(t_table *table)
{
	int	i;

	i = -1;
	while (table->philo_sum > ++i)
	{
		if (pthread_join(table->thread[i], NULL))
			clean_and_exit(table);
		usleep(10 * 1000);
	}
	if (pthread_join(table->monitor, NULL) != 0)
		clean_and_exit(table);
}
