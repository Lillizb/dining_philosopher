#include "philo.h"

void data_init(t_table *table, int ac, char **av)
{
	int	i;

	i = 0;
	table->philo_sum = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	table->philo = malloc(sizeof(t_philo) * table->philo_sum);
	table->fork = malloc(sizeof(t_fork) * table->fork_sum);
	if (ac == 6)
		table->meal_num = ft_atol(av[5]);
	else
		table->meal_num = -1; //no meal count is setted
	if (pthread_mutex_init(&table->table_mutex, NULL) != 0)
		//TODO error_exit();
}

void philo_init(t_table *table)
{
	int i;

	i = 0;
	while (table->philo_sum > i)
	{
		table->philo[i].data = table;
		table->philo->id = i + 1;
		table->philo->full = false; //what is this? time_to_sleep?
		table->philo->meal_counter = 0;
		table->philo->data = table;
		if (pthread_mutex_init(&table->philo[i].philo_mutex, NULL) != 0)
			//TODO exit_error(errormessage, table);
		assign_fork(&table->philo[i], table->fork, i);
		i++;
	}
	
}
void assign_fork(t_philo *philo, t_fork *fork, int philo_id)
{
	// int i;
	int philo_sum;

	philo_sum = philo->data->philo_sum;

	philo->second_fork = &fork[philo_id];
	philo->first_fork = &fork[(philo_id - 1) % philo_sum];
	if (philo_id % 2 == 0)
	{
		philo->first_fork = &fork[philo_id];
		philo->second_fork = &fork[(philo_id - 1) % philo_sum];
	}
}


//GPT：
/*
void assign_fork(t_philo *philo, t_fork *forks, int philo_id) {
    int philo_sum = philo->table->philo_sum;

    philo->first_fork = &forks[philo_id].mutex;
    philo->second_fork = &forks[(philo_id + 1) % philo_sum].mutex;
    if (philo_id % 2 == 0) {
        philo->first_fork = &forks[(philo_id + 1) % philo_sum].mutex;
        philo->second_fork = &forks[philo_id].mutex;
    }
}

void philo_init(t_table *table) {
    int i;
    t_philo *philo;

    i = 0;
    while (i < table->philo_sum) {
        philo = &table->philo[i];
        philo->id = i + 1;
        printf("philo ID: %d\n", philo->id);
        philo->full = false;
        philo->meal_counter = 0;
        philo->table = table;
        assign_fork(philo, table->forks, i);
        i++;
    }
}

void data_init(t_table *table) {
    int i;

    table->philo = malloc(sizeof(t_philo) * table->philo_sum);
    table->forks = malloc(sizeof(t_fork) * table->philo_sum);
    if (!table->philo || !table->forks) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < table->philo_sum; i++) {
        pthread_mutex_init(&table->forks[i].mutex, NULL);
        table->forks[i].fork_id = i;
    }
    pthread_mutex_init(&table->counter_mutex, NULL);
    philo_init(table);
}

//////////////////////////////////////////
*/



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
