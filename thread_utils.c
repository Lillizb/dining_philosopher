/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:34:58 by ygao              #+#    #+#             */
/*   Updated: 2024/10/16 12:37:41 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void destroy_mutex_exit(t_table *table)
{
	
}
