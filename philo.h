/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:52:59 by ygao              #+#    #+#             */
/*   Updated: 2024/11/23 13:37:03 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h> //get time of day
#include <limits.h> //INT_MAX

#define RESET "\033[0m" //reset to default color
#define R "\033[31m" //red
#define G "\033[32m" //green
#define Y "\033[33m"	 //yellow
#define B "\033[34m" //blue

//THREAD ERROR
#define MUTEX_ERR "ERROR WITH CREATING MUTEX!\n"
#define ALLOC_ERR_PHILO	"ERROR WITH ALLOCATING PHILO MEMORY!\n"
#define ALLOC_ERR_FORK	"ERROR WITH ALLOCATING FORK MEMORY!\n"
#define ALLOC_ERR_THREAD "ERROR WITH ALLOCATING THREAD MEMORY!\n"
#define ALLOC_TABLE_ERR "ERROR WITH ALLOCATING TABLE MEMORY!\n"
#define MEMORY_ALLOCATION_ERROR "MEMORY ALLOCATION ERROR\n"
typedef struct s_table	t_table;

typedef struct s_fork
{
	pthread_mutex_t		mutex;
}	t_fork;

typedef struct s_philo
{
	int				id;
	long			dead;
	long			meal_counter;
	long			must_eat;
	long			last_meal_time;
	bool			eating;
	bool			full; 
	pthread_t		thread;
	pthread_mutex_t	full_mutex;
	pthread_mutex_t	mutex;
	pthread_mutex_t	meal_mutex; 
	t_fork			*fork;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	long			start_time;
	long			philo_sum;
	long			thread_sum;
	long			fork_sum;
	long			full_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	bool			ready;
	bool			end_simulation;
	pthread_t		monitor;
	pthread_mutex_t	mutex;
	//pthread_mutex_t	start;
	pthread_mutex_t	write_mutex;
	t_philo			*philo;
	t_fork			*fork;
}	t_table;

typedef enum e_symbol
{
	THINKING,
	EATING,
	SLEEPING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	FREE_FIRST_FORK,
	FREE_SECOND_FORK,
	DIED,
}	t_symbol;

/******** Prototype ***********/
int		main(int ac, char **av);
void	one_philo(t_table *table);
void	*one(void *data);

/****** parsing input ******/
void	parse_input(int ac, char **av);
int		check_ac(int ac);
void	input_valid_check(char *str);



/******** data init ********/
void	data_init(t_table *table, int ac, char **av);
void	fork_init(t_table *table);
void	philo_init(t_table *table);
void	create_thread(t_table *table);
void	*monitor(void *data);
void	join_threads(t_table *table);

/*********** dining ************/
void	*routine(void *data);
void	think(t_philo *philo);
void	eat_schedule(t_philo *philo, t_table *table);
void	eat(t_philo *philo, t_table *table);
void	check_must_eat(t_philo *philo);


/******* utils *********/
bool	read_bool(pthread_mutex_t *mutex, bool *value);
void	take_fork(t_philo *philo, t_table *table);
void	free_fork(t_philo *philo, t_table *table);
long	get_time(void);
void	write_message(t_symbol symbol, t_philo *philo);
long	get_microseconds(void);
int		is_digit(char *s);
void	ft__exit(t_table *table);
long	ft_atol(char *str);
void	clean_and_exit(t_table *table);
int		error_exit(char *error, t_table *table);
void	free_struct(t_table *table);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strlen(const char *s);
int		is_space(char c);
void	ft_usleep(long time);
void	wait_for_start(t_table *table);
bool	end_simulation(t_table *table);
bool threads_all_running(t_table *table);

#endif
