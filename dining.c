#include "philo.h"
//create all philos, all threads

//create a monitor thread  --> what is this?

//sycronize the beginning of the simulation
	// pthread_create -> philo start running
	//	every philo starts simutaneously
// join everyone

//( if no meals, return ;
//	if there is only one philo, TODO)

void dining(t_table *table)
{
	int i;
	pthread_t *threads;

	threads = malloc(table->philo_sum * sizeof(pthread_t));
	i = 0;
	while (i <= table->philo_sum)
	{
		table->philo->id = i + 1;
		pthread_create(&threads[i], NULL, threadFunction, NULL);
		i++;
	}
	i = 0;
	while (i < table->philo_sum)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}
void threadFunction(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	printf("philosopher %d is eating\n", philo->id);

	return NULL;
}
