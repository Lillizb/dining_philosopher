/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:54:25 by ygao              #+#    #+#             */
/*   Updated: 2024/07/03 14:38:57 by ygao             ###   ########.fr       */
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
	if (ac == 6)
		table->must_eat = ft_atol(av[5]);
	else
		table->must_eat = -1;
	if (pthread_mutex_init(&table->table_mutex, NULL) != 0)
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
		if (pthread_mutex_init(&table->philo[i].philo_mutex, NULL) != 0)
			exit_error(MUTEX_ERR, table);
	}
}

void	fork_init(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_sum)
	{
		if (pthread_mutex_init(&table->fork[i].fork_mutex, NULL) != 0)
			exit_error(table);
	}
	i = 0;
	pthread_mutex_lock(&table->philo->philo_mutex);
	table->philo[0].second_fork = &table->fork[i];
	table->philo[0].first_fork = &table->fork[table->philo_sum - 1];
	assign_fork(table, i);
	pthread_mutex_unlock(&table->philo->philo_mutex);
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
