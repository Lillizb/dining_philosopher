/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:04:16 by ygao              #+#    #+#             */
/*   Updated: 2024/12/09 13:18:49 by ygao             ###   ########.fr       */
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
	{
		one_philo(table);
		return ;
	}
	if (pthread_create(&table->monitor, NULL, &monitor, table) != 0)
		error_exit(ALLOC_ERR_THREAD, table);
	while (++i < table->philo_sum)
	{
		if (pthread_create(&table->philo[i].thread, NULL, 
				&routine, &table->philo[i]) != 0)
			error_exit(ALLOC_ERR_THREAD, table);
	}
	pthread_mutex_lock(&table->mutex);
	table->start_time = get_microseconds();
	table->ready = true;
	pthread_mutex_unlock(&table->mutex);
	join_threads(table);
}

void	check_philos(t_table *table)
{
	int		i;
	long	g;

	i = -1;
	while (++i < table->philo_sum)
	{
		pthread_mutex_lock(&table->philo[i].mutex);
		g = get_microseconds() - table->philo[i].last_meal_time;
		if (!table->philo[i].eating && g > table->time_to_die)
		{
			write_message (DIED, &table->philo[i]);
			set_bool(&table->mutex, &table->end_simulation, true);
		}
		if (table->philo[i].meal_counter == table->philo[i].must_eat 
			&& !table->philo[i].full)
		{
			table->philo[i].full = true;
			pthread_mutex_lock(&table->mutex);
			table->full_philo++;
			if (table->full_philo == table->philo_sum)
				table->end_simulation = true;
			pthread_mutex_unlock(&table->mutex);
		}
		pthread_mutex_unlock(&table->philo[i].mutex);
	}
}

void	set_bool(pthread_mutex_t *mutex, bool *flag, bool value)
{
	pthread_mutex_lock(mutex);
	*flag = value;
	pthread_mutex_unlock(mutex);
}

void	*monitor(void *data)
{
	t_table	*table;

	table = data;
	while (!threads_all_running(table))
		usleep(100);
	while (!end_simulation(table))
		check_philos(table);
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
	}
	if (pthread_join(table->monitor, NULL) != 0)
		clean_and_exit(table);
}
