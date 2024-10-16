/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:34:58 by ygao              #+#    #+#             */
/*   Updated: 2024/10/16 16:45:24 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (table->philo_sum > i)
	{
		if (pthread_join(table->thread[i], NULL))
			return (exit_clean());//TODO
		usleep(10 * 1000);
	}
	if (table->philo->must_eat > -1)
	{
		if (pthread_join(table->philo->monitor, NULL) != 0)
			return (exit_clean());//TODO
	}
}

void exit_clean() //TODO
{
	
}
