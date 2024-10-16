/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:54:13 by ygao              #+#    #+#             */
/*   Updated: 2024/10/16 17:42:06 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data; 
	pthread_mutex_lock(&philo->table->mutex);
	if (philo->table->ready == true)
	{
		pthread_mutex_unlock(&philo->table->mutex);
		pthread_mutex_lock(&philo->mutex);
		philo->last_meal_time = get_time();
		pthread_mutex_unlock(&philo->mutex);
		eat_schedule(philo, philo->table);
		philo_eat(philo, philo->table);
	}
	else
		pthread_mutex_unlock(&philo->table->mutex);
}

void	eat_schedule(t_philo *philo, t_table *table)
{
	if (table->philo_sum % 2 == 0)
	{
		if (philo->id % 2 == 0)
			usleep(30 * 1000);
	}
	else 
	{
		if (philo->id % 2 != 0)
			think(philo, table);
	}
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
	pthread_mutex_lock(&philo->mutex);
	philo->meal_counter++; 
	philo->eating == 0;
	pthread_mutex_unlock(&philo->mutex);
	while (philo->dead == 0 && table->end_simulation == false)
	{
		eat(philo, table);
		write_message("SLEEPUNG", philo);
		usleep(table->time_to_sleep * 1000);
		think(philo, table);
	}
}

void	eat(t_philo *philo, t_table *table)
{
	if (table->end_simulation == false && philo->dead == 0)
	{
		philo->last_meal_time = get_time();
		write_message("EATING", philo);
		pthread_mutex_lock(&philo->meal_mutex);
		philo->eating == 1;
		pthread_mutex_unlock(&philo->meal_mutex);
		usleep(philo->table->time_to_eat * 1000);
		check_must_eat(philo);
	}
}

void	think(t_philo *philo, t_table *table)
{
	long	think_time;

	if (table->end_simulation == false)
		write_message("THINKING", philo);
	if (philo->id % 2 == 0)
		return ;
	think_time = (table->time_to_eat * 2) - table->time_to_sleep;
	if (think_time < 0)
		think_time = 0;
	usleep(think_time * 1000);
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
