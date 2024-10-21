/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:05:28 by ygao              #+#    #+#             */
/*   Updated: 2024/10/21 12:53:50 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo, t_table *table)
{
	long	think_time;

	if (table->end_simulation == false)
		write_message(THINKING, philo);
	if (philo->id % 2 == 0)
		return ;
	think_time = (table->time_to_eat * 2) - table->time_to_sleep;
	if (think_time < 0)
		think_time = 0;
	usleep(think_time * 1000);
}
