/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:00:38 by ygao              #+#    #+#             */
/*   Updated: 2024/07/03 13:05:42 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_exit(char *error, t_table *table)
{
	printf("%s\n", error);
	if (table)
		ft_exit(table);
	return (-1);
}

void ft__exit(t_table *table)
{
	
}
