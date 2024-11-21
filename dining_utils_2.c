/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:32:16 by ygao              #+#    #+#             */
/*   Updated: 2024/11/20 14:36:06 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool threads_all_running(t_table *table)
{
    bool    running;

    running = false;
    pthread_mutex_lock(&table->mutex);
    if (table->thread_sum == table->philo_sum)
        running = true;
    pthread_mutex_unlock(&table->mutex);
    return (running);
}