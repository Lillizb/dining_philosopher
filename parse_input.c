
#include "philo.h"

void	parse_input(int ac, char **av)
{
	int	i;

	i = 1;
	if ((check_ac(ac)) == -1)
		exit(EXIT_FAILURE);
	while (i < ac)
	{
		if (input_valid_check(av[i]) == -1)
		{
			printf("Error: Invalid input for argument %d: %s\n", i, av[i]);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

int	check_ac(int ac)
{
	if (ac < 5 || ac > 6)
		return (-1);
	return (0);
}

int	input_valid_check(char *str)
{
	int	len;

	len = 0;
	if (is_digit(str) == -1)
		return (-1);
	while (str[len] != '\0')
		len++;
	if (len > 10)
		return (-1);
	return (0);
}

int	is_digit(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '-')
			return (-1);
		if (s[i] == '\0')
			return (-1);
		if (s[i] == '+')
			i++;
		while (s[i] != '\0')
		{
			if (s[i] < '0' || s[i] > '9')
				return (-1);
			i++;
		}
	}
	return (0);
}
