#include "philo.h"

void data_init(t_table *table)
{
	int	i;

	i = 0;
	table->philo = malloc(sizeof(t_philo) * table->philo_sum);
	table->fork = malloc(sizeof(t_fork) * table->fork_sum);
	while (i < table->philo_sum)
	{
		pthread_mutex_init(&table->fork[i], NULL);
		table->fork[i].fork_id = i;
		i++;
	}
	philo_init(table);
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
		printf("philo ID: %ld\n", philo->id);
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

// void	mutex_handle(t_table *table, t_opcode opcode)
// {
// 	if (opcode == LOCK)
// 		pthread_mutex_lock(table->philo->id);
// 	else if (opcode == UNLOCK)
// 		pthread_mutex_unlock(table->philo->id);
// 	else if (opcode == INIT)
// 		pthread_mutex_init(table->philo->id, NULL);
// 	else if (opcode == DESTROY)
// 		pthread_mutex_destroy(table->philo->id);
// }

// void	thread_handle(t_table *table, t_opcode opcode)
// {
// 	if (opcode == CREATE)
// 		pthread_create(&table->philo->id, NULL, threadFunction, NULL);//threadFunction what is this?
// 	if (opcode == JOIN)
// 		pthread_join(table->philo->id, NULL);
// 	if (opcode == DETACH)
// 		pthread_detach(table->philo->id);
// }

// void* threadFunction(void* arg)
// {
// 	printf("philo is thiking\n");
// 	usleep(200);
// 	printf("philo sleeps");
// 	return NULL;
// }
