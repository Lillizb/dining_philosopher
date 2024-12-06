/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:54:07 by ygao              #+#    #+#             */
/*   Updated: 2024/12/06 17:45:17 by ygao             ###   ########.fr       */
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

	table = (t_table *)data;
	philo = table->philo;
	philo->last_meal_time = get_microseconds();
	write_message(TAKE_FIRST_FORK, philo);
	if (table->time_to_die - (get_microseconds() 
			- philo->last_meal_time) > 0)
		ft_usleep(table->time_to_die - (get_microseconds() 
				- philo->last_meal_time));
	write_message(DIED, philo);
	return (NULL);
}

void	one_philo(t_table *table)
{
	if (pthread_create(&table->philo->thread, NULL, &one, table) != 0)
		error_exit(ALLOC_ERR_THREAD, table);
	if (pthread_join(table->philo->thread, NULL) != 0)
		error_exit(ALLOC_JOIN_THREAD, table);
	clean_and_exit(table);
}
