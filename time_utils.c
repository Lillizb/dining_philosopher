/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:34:27 by ygao              #+#    #+#             */
/*   Updated: 2024/12/09 16:33:46 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_for_start(t_table *table)
{
	while (!read_bool(&table->mutex, &table->ready))
		ft_usleep(100);
}

long	get_microseconds(void)
{
	struct timeval	tv;
	long			microseconds;

	if (gettimeofday(&tv, NULL))
		return (1);
	microseconds = (long)((tv.tv_sec) * 1e6 + (long)(tv.tv_usec));
	return (microseconds);
}

void	ft_usleep(long time)
{
	long	left_time;
	long	start;

	start = get_microseconds();
	while ((get_microseconds() - start) < time)
	{
		left_time = time - (get_microseconds() - start);
		if (left_time > 1e4)
			usleep(left_time / 2);
		else
		{
			while ((get_microseconds() - start) < time)
				;
		}
	}
}

void	set_bool(pthread_mutex_t *mutex, bool *flag, bool value)
{
	pthread_mutex_lock(mutex);
	*flag = value;
	pthread_mutex_unlock(mutex);
}
