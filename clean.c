/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:00:38 by ygao              #+#    #+#             */
/*   Updated: 2024/10/21 11:11:11 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_exit(t_table *table)
{
	free(table);
	exit(EXIT_FAILURE);
}

int	error_exit(char *error, t_table *table)
{
	printf("%s\n", error);
	if (table)
		ft_exit(table);
	return (-1);
}

void	clean_and_exit(t_table *table)
{
	free_struct(table);
	free(table);
	exit(EXIT_SUCCESS);
}

void	free_struct(t_table *table)
{
	if (table->fork)
		free(table->fork);
	if (table->philo)
		free(table->philo);
}
