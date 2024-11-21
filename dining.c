/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:54:13 by ygao              #+#    #+#             */
/*   Updated: 2024/11/21 16:42:07 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *data)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)data;
	table = philo->table;
	wait_for_start(table);
	pthread_mutex_lock(&philo->table->mutex);
	table->thread_sum++;
	pthread_mutex_unlock(&philo->table->mutex);
	eat_schedule(philo, table);
	while (!end_simulation(table))
	{
		philo_eat(philo, table);
		write_message(SLEEPING, philo);
		think(philo, table);
		//usleep(table->time_to_sleep * 1000);
        write_message(THINKING, philo);
		// check_must_eat(philo);
	}
	return (NULL);
}

void	eat_schedule(t_philo *philo, t_table *table)
{
	if (table->philo_sum % 2 == 0)
	{
		if (philo->id % 2 == 0)
			ft_usleep(30000);
	}
	else
	{
		if (philo->id % 2)
			think(philo, table);
	}
}

void	philo_eat(t_philo *philo, t_table *table)
{
	if (table->philo_sum == 1)
	{
		usleep(table->time_to_die * 1000);
		return ;
	}
	take_fork(philo, table);
	eat(philo, table);
	free_fork(philo, table);
	pthread_mutex_lock(&philo->mutex);
	philo->meal_counter++; 
	philo->eating = 0;
	pthread_mutex_unlock(&philo->mutex);
	while (philo->dead == 0 && read_bool(&philo->table->mutex,
			&philo->table->end_simulation) == false)
	{
		pthread_mutex_lock(&philo->meal_mutex);
		if (philo->eating == 0)
		{
			pthread_mutex_unlock(&philo->meal_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->meal_mutex);
		if (read_bool(&philo->table->mutex,
				&philo->table->end_simulation) == true)
			break ;
		eat(philo, table);
		write_message(SLEEPING, philo);
		usleep(table->time_to_sleep * 1000);
		think(philo, table);
	}
}

void	eat(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(&philo->mutex);
	philo->last_meal_time = get_microseconds();
	printf("philo %d last meal time: %ld\n", philo->id, philo->last_meal_time);
	pthread_mutex_unlock(&philo->mutex);
	write_message(EATING, philo);
	// pthread_mutex_lock(&philo->meal_mutex);
	// philo->eating = 1;
	// pthread_mutex_unlock(&philo->meal_mutex);
	usleep(table->time_to_eat * 1000);
	pthread_mutex_lock(&philo->mutex);
	philo->meal_counter++;
	pthread_mutex_unlock(&philo->mutex);
	check_must_eat(philo);
}

void	check_must_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	if (philo->must_eat != -1 && philo->meal_counter 
		== philo->must_eat && philo->full == false)
	{
		philo->full = true;
		philo->table->full_philo++;
		if (philo->table->full_philo == philo->table->philo_sum)
			philo->table->end_simulation = true;
	}
	pthread_mutex_unlock(&philo->mutex);
}
