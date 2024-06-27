#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h> //get time of day
#include <limits.h> //INT_MAX

//fork

//phil 5 800 300 200
typedef struct s_fork
{
	int fork_id;
	bool fork_ok;
	pthread_t mutex;
	struct s_table *table;
	//t_philo *philo;

	//pthread_mutex_t mutex;
}	t_fork;

typedef struct s_philo
{
	long id;
	long meal_counter;
	pthread_mutex_t *first_fork;
	pthread_mutex_t *second_fork;
	bool full; 

	struct	s_table	*table;
	t_fork	*fork;

	//pthread_mutex_t mutex;
} t_philo;

typedef struct s_table
{
	t_philo *philo;
	t_fork *fork;
	long philo_sum;
	long fork_sum;
	pthread_mutex_t mutex;
	pthread_mutex_t *forks;
	bool	end_simulation;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;

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
void data_init(t_table *table);
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
