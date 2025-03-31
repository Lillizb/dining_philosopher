
#include "philo.h"

void	think(t_philo *philo, bool ready_process)
{
	long	t_eat;
	long	t_sleep;
	long	t_wait;

	if (!ready_process)
		write_message(THINKING, philo);
	if (philo->table->philo_sum % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_wait = (t_eat * 2) - t_sleep;
	if (t_wait < 0)
		t_wait = 0;
	ft_usleep(t_wait * 0.42);
}
