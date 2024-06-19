/*
			ms
./phil 5 800 200 200
1. actual numbers
2. not > INT_MAX
3. timestamps > 60ms
*/

#include "philo.h"

void parse_inout(t_table *table, char **av)
{
	table->phil_sum = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat =  ft_atol(av[3]);
	table->time_to_sleep =  ft_atol(av[4]);

	input_valid_check(table->phil_sum);
	input_valid_check(table->time_to_eat);
	input_valid_check(table->time_to_sleep);
	input_valid_check(table->time_to_die);
}
