#include "philo.h"

void	ft_exit(t_table *table)
{
	free(table);
	exit(EXIT_FAILURE);
}

int	error_exit(char *error, t_table *table)
{
	printf("%s\n", error);
	if (table)
		ft_exit(table);
	return (-1);
}

void	clean_and_exit(t_table *table)
{
	free_struct(table);
	free(table);
	exit(EXIT_SUCCESS);
}

void	free_struct(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_sum)
	{
		pthread_mutex_destroy(&table->philo[i].mutex);
		i++;
	}
	i = 0;
	while (i < table->philo_sum)
	{
		pthread_mutex_destroy(&table->fork[i].mutex);
		i++;
	}
	free(table->fork);
	free(table->philo);
	pthread_mutex_destroy(&table->mutex);
	pthread_mutex_destroy(&table->write_mutex);
}
