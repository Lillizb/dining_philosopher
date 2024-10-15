/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:54:13 by ygao              #+#    #+#             */
/*   Updated: 2024/10/15 17:40:29 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_routine(t_table *table, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < table->philo_sum)
	{
		join_threads(table);
		check_must_eat(philo);
		philo_eat(philo);

	}

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

void	write_message(char *s, t_philo *philo)
{
	long	time;

	if (philo->table->end_simulation == true)
		return ;
	time = get_time() - philo->table->start_time;
	pthread_mutex_lock(&philo->table->write_mutex);
	if (ft_strcmp("DIED", s) == 0)
		printf(R" %ld %d died\n"B, time, philo->id);
	if (ft_strcmp("EATING", s) == 0 && philo->table->end_simulation == true)
		printf(G" %ld %d is eating\n"B, time, philo->id);
	if (ft_strcmp("SLEEPING", s) == 0 && philo->table->end_simulation == true)
		printf(" %ld %d is sleeping\n", time, philo->id);
	if (ft_strcmp("TAKE_FIRST_FORK", s) == 0 
		&& philo->table->end_simulation == true)
		printf(" %ld %d has taken a fork\n", time, philo->id);
	if (ft_strcmp("TAKE_SECOND_FORK", s) == 0 
		&& philo->table->end_simulation == true)
		printf(" %ld %d has taken a fork\n", time, philo->id);
	if (ft_strcmp("THINKING", s) == 0 && philo->table->end_simulation == true)
		printf(" %ld %d is thinking\n", time, philo->id);
	pthread_mutex_unlock(&philo->table->write_mutex);
}

void	eat(t_philo *philo, t_table *table)
{
	philo->last_meal_time = get_time();
	if (philo->last_meal_time - table->start_time <= table->time_to_die)
		write_message("EATING", philo);
	usleep(philo->table->time_to_eat * 1000);
	philo->meal_counter++;
	check_must_eat(philo);
}

void	philo_eat(t_philo *philo, t_table *table)
{
	if (philo->table->end_simulation)
		return ;
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
	eat(philo, table);
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
