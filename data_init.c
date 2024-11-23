/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:54:25 by ygao              #+#    #+#             */
/*   Updated: 2024/11/22 20:05:04 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	data_init(t_table *table, int ac, char **av)
{
	table->philo_sum = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	table->fork_sum = table->philo_sum;
	table->philo = malloc(sizeof(t_philo) * table->philo_sum);
	if (!table->philo)
		error_exit(ALLOC_ERR_PHILO, table);
	table->fork = malloc(sizeof(t_fork) * table->philo_sum);
	if (!table->fork)
	{
		free(table->philo);
		error_exit(ALLOC_ERR_FORK, table);
	}
	table->thread_sum = 0;
	table->ready = false;
	table->full_philo = 0;
	printf("Philosophers: %ld\n", table->philo_sum);
	printf("Time to die: %ld\n", table->time_to_die);
	table->end_simulation = false;
	table->start_time = 0;
	table->philo->must_eat = -1;
	if (ac == 6)
		table->philo->must_eat = ft_atol(av[5]);
	if (pthread_mutex_init(&table->mutex, NULL) != 0)
		error_exit(MUTEX_ERR, table);
	if (pthread_mutex_init(&table->write_mutex, NULL) != 0)
		error_exit(MUTEX_ERR, table);
	philo_init(table);
	fork_init(table);
}

void	philo_init(t_table *table)
{
	long	i;

	i = -1;
	while (table->philo_sum > ++i)
	{
		table->philo[i].table = table;
		table->philo[i].fork = table->fork;
		table->philo[i].id = i + 1;
		table->philo[i].dead = 0;
		table->philo[i].meal_counter = 0;
		table->philo[i].must_eat = table->philo->must_eat;
		table->philo[i].eating = false;
		table->philo[i].full = false;
		table->philo[i].last_meal_time = 0;
		if (pthread_mutex_init(&table->philo[i].mutex, NULL) != 0)
			error_exit(MUTEX_ERR, table);
	}
}

void	fork_init(t_table *table)
{
	int		i;

	i = -1;
	while (++i < table->philo_sum)
	{
		if (pthread_mutex_init(&table->fork[i].mutex, NULL) != 0)
			error_exit(MUTEX_ERR, table);
	}
}
