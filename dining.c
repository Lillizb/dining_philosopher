/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:54:13 by ygao              #+#    #+#             */
/*   Updated: 2024/10/16 13:24:50 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data; 
	philo_eat(philo, philo->table);
}

void	philo_eat(t_philo *philo, t_table *table)
{
	take_fork(philo, table);
	if (table->philo_sum == 1)
	{
		usleep(table->time_to_die * 1000);
		return ;
	}
	eat(philo, table);
	free_fork(philo, table);
}

void	eat(t_philo *philo, t_table *table)
{
	if (table->end_simulation == false && philo->dead == 0)
	{
		philo->last_meal_time = get_time();
		write_message("EATING", philo);
		usleep(philo->table->time_to_eat * 1000);
		pthread_mutex_lock(&philo->meal_mutex);
		philo->meal_counter++; 
		pthread_mutex_unlock(&philo->meal_mutex);
		check_must_eat(philo);
	}
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

int	monitor(t_table *table)
{
	long	time;

	time = get_time();
	if (time - table->start_time >= table->time_to_die)
	{
		printf ("%ld philosopher %d died\n", time, table->philo->id);
		return (-1);
	}
}

