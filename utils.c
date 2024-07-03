/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:52:45 by ygao              #+#    #+#             */
/*   Updated: 2024/07/03 10:52:48 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
//print error

int	input_valid_check(char *str)
{
	int	len;

	len = 0;

	if (is_digit(str) == 0)
	{
		printf("The input is not digit");
		return (0);
	}
	while (str[len] != '\0')
		len++;
	if (len > 10)
	{
		printf("The input is greater than INT_MAX, illegal");
		return (0);
	}
}

int	is_digit(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '-' || s[i] == '+')
			i++;
		if (s[i] == '\0')
			return (0);
		while (s[i] != '\0')
		{
			if (s[i] < '0' && s[i] > '9')
				return (0);
			i++;
		}
	}
	return (1);
}

int	is_space(char str)
{
	if (str == ' ' || str == '\t' || str == '\n' 
		|| str == '\v' || str == '\f' || str == '\r')
		return (1);
	return (0);
}

long	ft_atol(char *str)
{
	int		i;
	long	n;
	int		sign;

	i = 0;
	n = 0;
	sign = 1;
	while (str[i] != '\0')
	{
		if (is_space(str[i]) == 1)
			i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	return (n * sign);
}

void*	my_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (ret == NULL)
		return (NULL);
	return (ret);
}
