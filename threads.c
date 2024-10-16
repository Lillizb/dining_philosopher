/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:04:16 by ygao              #+#    #+#             */
/*   Updated: 2024/10/16 17:49:45 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine(void *data);

void	create_thread(t_table *table)
{
	int	i;

	i = -1;
	if (table->philo->must_eat > -1)
	{
		if (pthread_create(&table->philo->monitor, NULL, &monitor, table) != 0)
			exit_clean(); //TODO
	}
	pthread_mutex_lock(&table->start);
	while (++i < table->philo_sum)
	{
		if (pthread_create(&table->thread[i], NULL, 
				&routine, &table->philo[i]) != 0)
		return (exit_clean()); //TODO
	}
	pthread_mutex_unlock(&table->start);
	pthread_mutex_lock(&table->mutex);
	if (i == table->philo_sum)
		table->ready == true;
	pthread_mutex_unlock(&table->mutex);
	thread_join(table);
}

void	*monitor(void *data)
{
	t_table	*table;

	table = (void *)data;
	while (table->philo->dead == 0)
	{
		pthread_mutex_lock(&table->mutex);
		if (table->full_philo == table->philo_sum)
			table->end_simulation = true;
		pthread_mutex_unlock(&table->mutex);
	}
	return (NULL);
}
