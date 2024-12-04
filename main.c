/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:54:07 by ygao              #+#    #+#             */
/*   Updated: 2024/12/02 16:08:17 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (table == NULL)
	{
		printf(ALLOC_TABLE_ERR);
		return (-1);
	}
	if (check_ac(ac) == -1)
	{
		free(table);
		return (-1);
	}
	if (ac == 5 || ac == 6)
	{
		parse_input(ac, av);
		data_init(table, ac, av);
		create_thread(table);
	}
	clean_and_exit(table);
}

void	*one(void *data)
{
	t_table	*table;
	t_philo	*philo;
	long	elapse;

	philo = (t_philo *)data;
	table = philo->table;
	table->start_time = get_microseconds();
	philo->last_meal_time = get_microseconds();
	write_message(TAKE_FIRST_FORK, philo);
	elapse = table->time_to_die - (get_microseconds() - philo->last_meal_time);
	if ((get_microseconds() - philo->last_meal_time) < table->time_to_die)
		ft_usleep(elapse);
	write_message(DIED, philo);
	return (NULL);
}

void	one_philo(t_table *table)
{
	if (table->philo_sum == 1)
	{
		if (pthread_create(&table->philo->thread, NULL, &one, table) != 0)
		{
			perror("Failed to create thread for single philosopher");
			//clean_and_exit(table);
		}
	}
	pthread_join(table->philo->thread, NULL);
	//clean_and_exit(table);
}
