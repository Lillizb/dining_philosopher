/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:54:13 by ygao              #+#    #+#             */
/*   Updated: 2024/12/06 17:37:48 by ygao             ###   ########.fr       */
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
	pthread_mutex_lock(&table->mutex);
	table->thread_sum++;
	pthread_mutex_unlock(&table->mutex);
	pthread_mutex_lock(&philo->mutex);
	philo->last_meal_time = get_microseconds();
	pthread_mutex_unlock(&philo->mutex);
	eat_schedule(philo, table);
	while (!end_simulation(table))
	{
		eat(philo, table);
		write_message(SLEEPING, philo);
		ft_usleep(table->time_to_sleep);
		think(philo, false);
	}
	return (NULL);
}

void	eat_schedule(t_philo *philo, t_table *table)
{
	if (table->philo_sum % 2 == 0)
	{
		if (philo->id % 2 == 0)
			ft_usleep(1000);
	}
	else
	{
		if (philo->id % 2)
			think(philo, true);
	}
}

void	eat(t_philo *philo, t_table *table)
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
		return ;
	pthread_mutex_lock(&philo->fork[first_fork].mutex);
	write_message(TAKE_FIRST_FORK, philo);
	pthread_mutex_lock(&philo->fork[second_fork].mutex);
	write_message(TAKE_SECOND_FORK, philo);
	write_message(EATING, philo);
	pthread_mutex_lock(&philo->mutex);
	philo->eating = true;
	philo->last_meal_time = get_microseconds();
	philo->meal_counter++; 
	pthread_mutex_unlock(&philo->mutex);
	ft_usleep(table->time_to_eat);
	pthread_mutex_unlock(&philo->fork[first_fork].mutex);
	pthread_mutex_unlock(&philo->fork[second_fork].mutex);
	pthread_mutex_lock(&philo->mutex);
	philo->eating = false;
	pthread_mutex_unlock(&philo->mutex);
}
