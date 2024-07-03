/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:53:52 by ygao              #+#    #+#             */
/*   Updated: 2024/07/03 14:41:11 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parse_input(t_table *table, int ac, char **av)
{
	input_valid_check(av[1]);
	input_valid_check(av[2]);
	input_valid_check(av[3]);
	input_valid_check(av[4]);
	if (ac == 6)
		input_valid_check(av[5]);

	table->philo_sum = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
		table->must_eat = ft_atol(av[5]);
}

int	check_ac(int ac)
{
	if (ac < 5 || ac > 6)
		return (1);
	return (0);
}
