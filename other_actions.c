/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:05:28 by ygao              #+#    #+#             */
/*   Updated: 2024/11/22 13:32:39 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (philo->table->philo_sum % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	ft_usleep(t_think * 0.42);
}
