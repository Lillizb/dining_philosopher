/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:52:59 by ygao              #+#    #+#             */
/*   Updated: 2024/07/03 14:40:52 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
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
#define MUTEX_ERR "ERROR WITH CREATING MUTEX!"
#define ALLOC_ERR_PHILO	"ERROR WITH ALLOCATING PHILO MEMORY!"
#define ALLOC_ERR_FORK	"ERROR WITH ALLOCATING FORK MEMORY!"

typedef struct s_fork
{
	pthread_mutex_t		fork_mutex;
}	t_fork;

typedef struct s_philo
{
	t_table			*table;
	int				id;
	bool			full; 
	t_fork			*first_fork;
	t_fork			*second_fork;
	long			meal_counter;
	pthread_mutex_t	philo_mutex;
}	t_philo;

typedef struct s_table
{
	t_philo			*philo;
	t_fork			*fork;
	long			philo_sum;
	long			fork_sum;
	pthread_mutex_t	table_mutex;
	pthread_mutex_t	write_mutex;
	bool			end_simulation;
	long			must_eat;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
}	t_table;

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
int		main(int ac, char **av);


/****** parsing input ******/
void	parse_input(t_table *table, int ac, char **av);
int		check_ac(int ac);


/******** data init ********/
void	data_init(t_table *table, int ac, char **av);
void	fork_init(t_table *table);
void	assign_fork(t_table *table, int i);
void	philo_init(t_table *table);

/*********** dining ************/
void	dining(t_table *table);

/******* utils *********/
int		input_valid_check(char *str);
int		is_digit(char *s);
int		is_space(char str);
long	ft_atol(char *str);
void*	my_malloc(size_t bytes);


#endif
