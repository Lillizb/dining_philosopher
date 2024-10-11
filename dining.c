/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:54:13 by ygao              #+#    #+#             */
/*   Updated: 2024/10/11 18:15:08 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_routine(void )
{

}

void	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (table->philo_sum > i)
	{
		pthread_join(table->philo[i].thread, NULL);
		i++;
	}
}

void	philo_eat(t_philo *philo)
{
	if (philo->table->end_simulation)
        return ;
	philo->last_meal_time = get_time();
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->first_fork->mutex);
		pthread_mutex_lock(&philo->second_fork->mutex);
	}
	else
	{
		pthread_mutex_lock(&philo->second_fork->mutex);
		pthread_mutex_lock(&philo->first_fork->mutex);
	}
	pthread_mutex_lock(&philo->table->write_mutex);
	printf("philosopher %d is eating\n", philo->id);
	pthread_mutex_unlock(&philo->table->write_mutex);
	usleep(philo->table->time_to_eat * 1000);
	philo->meal_counter++;
	check_must_eat(philo);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->first_fork->mutex);
		pthread_mutex_unlock(&philo->second_fork->mutex);
	}
	else
	{
		pthread_mutex_unlock(&philo->second_fork->mutex);
		pthread_mutex_unlock(&philo->first_fork->mutex);
	}
}

void	check_must_eat(t_philo *philo)
{
	if (philo->must_eat != -1 && philo->meal_counter 
		== philo->must_eat && philo->full == false)
	{
		philo->full = true;
		pthread_mutex_lock(&philo->full_mutex);
		philo->table->full_philo++;
		if (philo->table->full_philo == philo->table->philo_sum)
			philo->table->end_simulation = true;
		pthread_mutex_unlock(&philo->full_mutex);
	}
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

long	get_time()
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

void	one_philo(t_philo *philo)
{
	if (philo->table->philo_sum == 1)
	{
		
	}
}
