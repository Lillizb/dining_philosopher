/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:54:07 by ygao              #+#    #+#             */
/*   Updated: 2024/12/10 13:39:51 by ygao             ###   ########.fr       */
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
	if (philo->table->end_simulation == true)
		return (NULL);
	printf(B "%ld 1 has taken a fork\n", table->start_time);
	ft_usleep(table->time_to_die);
	printf(R "%ld 1 died\n"B, table->time_to_die / 1000);
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
