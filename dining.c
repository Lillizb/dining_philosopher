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
	if (threads == NULL)
		exit(EXIT_FAILURE);
	i = 0;
	pthread_mutex_init(&table->mutex, NULL);

	while (i <= table->philo_sum)
	{
		table->philo->id = i + 1;
		if (pthread_create(&threads[i], NULL, threadFunction, &table->philo[i]) != 0)
			//TODO: free(threads); free(table->forks)? ; exit(EXIT_FAILURE);
		i++;
	}
	i = 0;
	while (i < table->philo_sum)
	{
		if (pthread_join(threads[i], NULL) != 0)
			//TODO: free(threads); free(table->forks)? ; exit(EXIT_FAILURE);
		i++;
	}
	pthread_mutex_destroy(&table->mutex);
	free(threads);
}
void threadFunction(void *arg)
{
	t_philo *philo;
	t_fork	*fork;

	t_philo philo = (t_philo *)arg;
	printf(THINKING "philosopher %d is thinking\n" RESET, philo->id);
	usleep(100);

	pthread_mutex_lock(philo->first_fork);
	printf("philosopher %d is taking the first fork\n", philo->id, fork->fork_id);
	pthread_mutex_lock(philo->second_fork);
	printf("philosopher %d is taking the second fork\n", philo->id, fork->fork_id);
	
	printf(EATING "philosopher %d is eating\n" RESET, philo->id);
	usleep(100);

	pthread_mutex_unlock(&philo->first_fork);
	pthread_mutex_unlock(&philo->second_fork);	
	
	printf("philosopher %d is sleeping\n", philo->id);
	usleep(100);

}

long get_time(void)
{
	struct timeval tv;
	long start;

	if (gettimeofday(&tv,NULL) != 0)
	{
		printf("Time Of Day: Error!\n");
		return (-1);
	}
	start = tv.tv_sec * 1e3 + tv.tv_usec / 1e3;
	return (start);
}

//eat 
	table->start_time = get_time(void);
	table->philo->death_time = table->start + table->time_to_die;
