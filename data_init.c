#include "philo.h"


void data_init(char **av)
{
	table->phil_sum = ft_atol(av[1]);
	table->fork_sum = table->phil_sum;
	table->philo = malloc(table->phil_sum);
	table->philo->id = 0; //?
	table->phil->full = false;
	//phil->mutex = 
}
void philo_init(t_table *table)
{
	int i;
	t_philo *philo;

	i = 0;
	while (table->philo_sum > i)
	{
		philo = &table->philo[i];
		philo->id = i + 1;
		printf("philo ID: %d\n", philo->id);
		philo->full = false;
		philo->meal_counter = 0;
		philo->table = table;
		i++;
	}
	assign_fork(philo, table->fork, i);
} 
void assign_fork(t_philo *philo, t_fork *fork, int philo_id)
{
	// int i;
	int philo_sum;

	philo_sum = philo->table->philo_sum;

	philo->second_fork = &fork[philo_id];
	philo->first_fork = &fork[(philo_id - 1) % philo_sum];
	if (philo_id % 2 == 0)
	{
		philo->first_fork = &fork[philo_id];
		philo->second_fork = &fork[(philo_id - 1) % philo_sum];
	}
}

//***** MUTEX SAFE ******//
/*
init 
destroy 
lock
unlock
*/

void mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		pthread_mutex_lock(mutex);
	else if (opcode == UNLOCK)
		pthread_mutex_unlock(mutex);
	else if (opcode = INIT)
		pthread_mutex_init(mutex, NULL);
	else if (opcode == DESTROY)
		pthread_mutex_destroy(mutex, NULL);
}

