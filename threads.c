
#include "philo.h"

void	create_thread(t_table *table)
{
	int	i;

	i = -1;
	if (table->philo->must_eat < -1 || table->philo_sum == 0)
		return ;
	if (table->philo_sum == 1)
	{
		one_philo(table);
		return ;
	}
	while (++i < table->philo_sum)
	{
		if (pthread_create(&table->philo[i].thread, NULL, 
				&routine, &table->philo[i]) != 0)
			error_exit(ALLOC_ERR_THREAD, table);
	}
	if (pthread_create(&table->monitor, NULL, &monitor, table) != 0)
		error_exit(ALLOC_ERR_THREAD, table);
	pthread_mutex_lock(&table->mutex);
	table->start_time = get_microseconds();
	table->ready = true;
	pthread_mutex_unlock(&table->mutex);
	join_threads(table);
	pthread_join(table->monitor, NULL);
}

void	*monitor(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	while (!threads_all_running(table))
		;
	while (!end_simulation(table))
	{
		i = -1;
		while (++i < table->philo_sum)
		{
			pthread_mutex_lock(&table->philo[i].mutex);
			if (!table->philo[i].eating && 
				((get_microseconds() - table->philo[i].last_meal_time)
					> table->time_to_die))
			{
				write_message(DIED, &table->philo[i]);
				set_bool(&table->mutex, &table->end_simulation, true);
			}
			check_philosopher_full(table, i);
			pthread_mutex_unlock(&table->philo[i].mutex);
		}
	}
	return (NULL);
}

void	check_philosopher_full(t_table *table, int i)
{
	if (table->philo[i].meal_counter == table->philo[i].must_eat 
		&& !table->philo[i].full) 
	{
		table->philo[i].full = true;
		pthread_mutex_lock(&table->mutex);
		table->full_philo++;
		if (table->full_philo == table->philo_sum)
			table->end_simulation = true;
		pthread_mutex_unlock(&table->mutex);
	}
}

void	join_threads(t_table *table)
{
	int	i;

	i = -1;
	while (table->philo_sum > ++i)
	{
		if (pthread_join(table->philo[i].thread, NULL))
			clean_and_exit(table);
	}
	if (pthread_join(table->monitor, NULL) != 0)
		clean_and_exit(table);
}
