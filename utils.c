#include "philo.h"
//print error

int	input_valid_check(char *str)
{
	char *nbr;
	int len;
	int i;

	i = 0;
	while (str[i])
	{
		if (is_digit(str[i]) == 0)
		{
			printf("The input is not a digit");
			return (0);
		}
		if (is_space(str[i]) == 1) //
			i++;
		if (len > 10) //len need to write a function
		printf("The input is greater than INT_MAX, illegal");
		i++;
	}

}

int is_digit(char *s)
{

}

int is_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\t')
			return (1);
		i++;
	}
	return (0);
}

long ft_atol(char *str)
{

}

void* my_malloc(size_t bytes)
{
	void *ret;

	ret = malloc(bytes);
	if (ret == NULL)
		return (NULL);
	return (ret);
}
