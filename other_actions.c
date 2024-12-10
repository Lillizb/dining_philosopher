/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:05:28 by ygao              #+#    #+#             */
/*   Updated: 2024/12/09 16:31:01 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo, bool ready_process)
{
	long	t_eat;
	long	t_sleep;
	long	t_wait;

	if (!ready_process)
		write_message(THINKING, philo);
	if (philo->table->philo_sum % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_wait = (t_eat * 2) - t_sleep;
	if (t_wait < 0)
		t_wait = 0;
	ft_usleep(t_wait * 0.42);
}
