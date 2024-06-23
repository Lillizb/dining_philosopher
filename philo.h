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
	int id;
	int meal_counter;
	t_fork *first_fork;
	t_fork *second_fork;
	bool full; 

	struct	s_table	*table;
	t_fork	*fork;

	//pthread_mutex_t mutex;
} t_philo;

typedef struct s_table
{
	t_philo *philo;
	t_fork *fork;
	int philo_sum;
	int fork_sum;
	int	meal_counter;
	bool	end_simulation;
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
int main();



/****** parsing input ******/
//void parse_inout(t_table *table, char **av);


/******** data init ********/
void assign_fork(t_philo *philo, t_fork *fork, int philo_id);
void philo_init(t_table *table);


/******* utils *********/
void* my_malloc(size_t bytes);
