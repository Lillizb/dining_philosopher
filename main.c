#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h> //sleep 

#include <sys/time.h>
#include "philo.h"

//5 800 200 200
/*
av[1] = number_of_philosophers
av[2] = time_to_die 
av[3] = time_to_eat
av[4] = time_to_sleep
*/

int main(int ac, char **av)
{
	t_table *table;

	if (ac != 5)
	{
		printf("");
	}
	if (ac == 5 || ac == 6)
	{
		parse_input(table, av);
		data_init(table);
		dining(table);

	}
	//1. parsing input
	
	//2. data init
	
	//3. dining start

	//4. no leaks
}
	// t_table table;

	// int philo_count = 5;
	// int fork_count = 5;

	// table.philo_sum = philo_count;
	// table.fork_sum = fork_count;
	

	//assign_fork(&table);

	// for(int i = 0; i < philo_count; i++)
	// {
	// 	printf("Philosopher: %d: id = %d, full=%d, meal_counter = %d\n",
	// 		i, table.philo[i].id, table.philo[i].full, table.philo->meal_counter);
	// }	
	// for(int i = 0; i < fork_count; i++)
	// {
	// 	printf("forks: %d: id=%d, fork_ok=%d\n",
	// 		i, table.fork[i].id, table.fork[i].fork_ok);
	// }

	free(table.philo);
	free(table.fork);
}

	


	// t_fork *fork;

	// i = 0;
	// while (table->fork_sum > i)
	// {
	// 	fork = &table->fork[i];
	// 	fork->id = i;
	// 	printf("fork ID: %d\n", fork->id);
	// 	fork->fork_ok = false;
	// 	i++;
	// }
// 	if (ac == 5)
// 	{
// 		//1. error checking, filling table
// 			parse_input(&table, av);
// 		//2. creating the actual thing
// 			data_init(&table);
// 		// 3. dinner start
// 			dinner_start(&table);
// 		//4. no leaks
// 			clean(&table) //philo is full or philo died
// 	}
// 	else
// 		//print error
// }


// pthread_mutex_t mutex;
// int philid = 0;

// void* phil(void* arg)
// {
// 	for(int i = 0; i < 5; i++)
// 	{
// 		pthread_mutex_lock(&mutex);
// 		philid += 1;
// 		printf("phil %d is here\n", philid);
// 		pthread_mutex_unlock(&mutex);
// 		sleep(1);
// 	}
// }

// // void* car(void *arg) 
// // {
// // 	if (pthread_mutex_lock(&mutex) == 0)
// // 	{
// // 		printf("thinking\n");
		
// // 		pthread_mutex_unlock(&mutex);
// // 		printf("unlock\n");
// // 		sleep(1);
// // 	}	
// // }

// int main(int ac, char **av)
// {
// 	pthread_t th[4];
// 	pthread_mutex_init(&mutex, NULL);
// 	for (int i = 0; i < 4; i++)
// 	{
// 		if (i == 1)
// 		{
// 			if (pthread_create(&th[i], NULL, &phil, NULL) != 0)
// 				perror("failed to create thread");
// 		}
// 		// else
// 		// {
// 		// 	if (pthread_create(&th[i], NULL, &car, NULL) != 0)
// 		// 		perror("failed to create thread");
// 		// }
// 	}
// 	for (int i = 0; i < 4; i++)
// 	{
// 		pthread_join(th[i], NULL)
// 			//perror("failed to join thread");
// 	}
// 	pthread_mutex_destroy(&mutex);
// 	return (0);
// }

pthread_create(&table->philo[i], NULL, &table->philo, NULL);
pthread_join(table->philo[i], NULL)
pthread_mutex_destroy(&table->philo[i]);
