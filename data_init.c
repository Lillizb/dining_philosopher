#include "philo.h"

void	data_init(t_table *table, int ac, char **av)
{
	data_init_util(table, av);
	table->fork_sum = table->philo_sum;
	table->philo = malloc(sizeof(t_philo) * table->philo_sum);
	if (!table->philo)
		error_exit(ALLOC_ERR_PHILO, table);
	table->fork = malloc(sizeof(t_fork) * table->philo_sum);
	if (!table->fork)
	{
		free(table->philo);
		error_exit(ALLOC_ERR_FORK, table);
	}
	table->thread_sum = 0;
	table->ready = false;
	table->full_philo = 0;
	usleep(1000);
	data_init_ii(table);
	if (ac == 6)
		table->philo->must_eat = ft_atol(av[5]);
	if (pthread_mutex_init(&table->mutex, NULL) != 0)
		error_exit(MUTEX_ERR, table);
	if (pthread_mutex_init(&table->write_mutex, NULL) != 0)
		error_exit(MUTEX_ERR, table);
	philo_init(table);
	fork_init(table);
}

void	data_init_util(t_table *table, char **av)
{
	table->philo_sum = (int)ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1000;
	table->time_to_eat = ft_atol(av[3]) * 1000;
	table->time_to_sleep = ft_atol(av[4]) * 1000;
}

void	data_init_ii(t_table *table)
{
	table->end_simulation = false;
	table->start_time = 0;
	table->philo->must_eat = -1;
}

void	philo_init(t_table *table)
{
	long	i;

	i = -1;
	while (table->philo_sum > ++i)
	{
		table->philo[i].table = table;
		table->philo[i].fork = table->fork;
		table->philo[i].id = i + 1;
		table->philo[i].dead = 0;
		table->philo[i].meal_counter = 0;
		if (table->philo->must_eat != -1)
			table->philo[i].must_eat = table->philo->must_eat;
		table->philo[i].eating = false;
		table->philo[i].full = false;
		table->philo[i].last_meal_time = 0;
		if (pthread_mutex_init(&table->philo[i].mutex, NULL) != 0)
			error_exit(MUTEX_ERR, table);
	}
}

void	fork_init(t_table *table)
{
	int		i;

	i = -1;
	while (++i < table->philo_sum)
	{
		if (pthread_mutex_init(&table->fork[i].mutex, NULL) != 0)
			error_exit(MUTEX_ERR, table);
	}
}
