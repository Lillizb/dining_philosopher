/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:54:25 by ygao              #+#    #+#             */
/*   Updated: 2024/10/11 17:58:16 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	data_init(t_table *table, int ac, char **av)
{
	int	i;

	i = 0;
	table->philo = malloc(sizeof(t_philo) * table->philo_sum);
	if (!table->philo)
		return (error_exit(ALLOC_ERR_PHILO, table));
	table->fork = malloc(sizeof(t_fork) * table->philo_sum);
	if (!table->philo)
	{
		free(table->philo);
		return (error_exit(ALLOC_ERR_FORK, table));
	}
	table->philo_sum = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	table->start_time = 0;
	table->full_philo = 0;
	table->end_simulation = false;
	if (ac == 6)
		table->philo->must_eat = ft_atol(av[5]);
	else
		table->philo->must_eat = -1;
	if (pthread_mutex_init(&table->mutex, NULL) != 0)
		error_exit(MUTEX_ERR, table);
	if (pthread_mutex_init(&table->write_mutex, NULL) != 0)
		error_exit(MUTEX_ERR, table);
}

void	philo_init(t_table *table)
{
	int	i;

	i = -1;
	while (table->philo_sum > ++i)
	{
		table->philo[i].table = table;
		table->philo[i].id = i + 1;
		table->philo[i].full = false;
		table->philo[i].meal_counter = 0;
		table->philo[i].last_meal_time = 0;
		assign_fork(table, i);
		if (pthread_mutex_init(&table->philo[i].mutex, NULL) != 0)
			exit_error(MUTEX_ERR, table);
	}
}

void	fork_init(t_table *table)
{
	int		i;
	t_fork	*fork;

	i = 0;
	while (i < table->philo_sum)
	{
		if (pthread_mutex_init(&table->fork[i].mutex, NULL) != 0)
			exit_error(MUTEX_ERR, table);
		i++;
	}
}

void	assign_fork(t_table *table, int i)
{
	while (++i < table->philo_sum)
	{
		if (i % 2 == 0)
		{
			table->philo[i].first_fork = &table->fork[i];
			table->philo[i].second_fork = &table->fork[(i + 1) 
				% table->philo_sum];
		}
		else
		{
			table->philo[i].second_fork = &table->fork[i];
			table->philo[i].first_fork = &table->fork[(i - 1) 
				% table->philo_sum];
		}
	}
}
