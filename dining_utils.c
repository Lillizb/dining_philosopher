
#include "philo.h"

bool	read_bool(pthread_mutex_t *mutex, bool *value)
{
	bool	result;

	pthread_mutex_lock(mutex);
	result = *value;
	pthread_mutex_unlock(mutex);
	return (result);
}

bool	end_simulation(t_table *table)
{
	bool	end;

	pthread_mutex_lock(&table->mutex);
	end = table->end_simulation;
	pthread_mutex_unlock(&table->mutex);
	return (end);
}

void	write_message(t_symbol	symbol, t_philo *philo)
{
	long		time;
	bool		end;

	end = read_bool(&philo->table->mutex, &philo->table->end_simulation);
	time = (get_microseconds() - philo->table->start_time) / 1000;
	pthread_mutex_lock(&philo->table->write_mutex);
	if (end)
	{
		pthread_mutex_unlock(&philo->table->write_mutex);
		return ;
	}
	if (symbol == DIED)
		printf(R " %ld %d died\n"B, time, philo->id);
	else if (symbol == EATING)
		printf(G " %ld %d is eating\n"B, time, philo->id);
	else if (symbol == SLEEPING)
		printf(Y " %ld %d is sleeping\n"B, time, philo->id);
	else if (symbol == TAKE_FIRST_FORK)
		printf(B " %ld %d has taken a fork\n", time, philo->id);
	else if (symbol == TAKE_SECOND_FORK)
		printf(" %ld %d has taken a fork\n", time, philo->id);
	else if (symbol == THINKING)
		printf(Y " %ld %d is thinking\n", time, philo->id);
	pthread_mutex_unlock(&philo->table->write_mutex);
}

bool	threads_all_running(t_table *table)
{
	bool	running;

	running = false;
	pthread_mutex_lock(&table->mutex);
	if (table->thread_sum == table->philo_sum)
		running = true;
	pthread_mutex_unlock(&table->mutex);
	return (running);
}
