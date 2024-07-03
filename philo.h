#ifndef	PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h> //get time of day
#include <limits.h> //INT_MAX

#define RESET   "\033[0m" //reset to default color
#define R    "\033[31m" //red
#define G   "\033[32m" //green
#define Y  "\033[33m"	 //yellow
#define B    "\033[34m" //blue


typedef struct s_fork
{
	pthread_t fork_mutex;
}	t_fork;

typedef struct s_philo
{
	int id;

	bool full; 
	t_fork *first_fork;
	t_fork *second_fork;
	t_table	*data;
	t_fork	*fork;
	pthread_mutex_t philo_mutex;
}	t_philo;

typedef struct s_table
{
	t_philo *philo;
	t_fork *fork;
	long philo_sum;
	long fork_sum;
	long meal_num; //av[5]
	pthread_mutex_t philo_mutex;
	pthread_mutex_t *forks;
	pthread_mutex_t table_mutex;
	bool	end_simulation;
	long	meal_counter;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	death_time;
	long	start_time;


} t_table;

//MUTEX
typedef enum e_opcode
{
	INIT,
	DESTROY,
	LOCK,
	UNLOCK,
	CREATE,
	JOIN,
	DETACH,
}	t_opcode;
	

/******** Prototype ***********/
int main(int ac, char **av);


/****** parsing input ******/
void parse_input(t_table *table, char **av);


/******** data init ********/
void data_init(t_table *table, int ac, char **av);
void assign_fork(t_philo *philo, t_fork *fork, int philo_id);
void philo_init(t_table *table);

/*********** dining ************/
void dining(t_table *table);

/******* utils *********/
int	input_valid_check(char *str);
int is_digit(char *s);
int is_space(char str);
long ft_atol(char *str);
void* my_malloc(size_t bytes);


#endif
