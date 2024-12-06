/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygao <ygao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:53:52 by ygao              #+#    #+#             */
/*   Updated: 2024/12/06 17:18:41 by ygao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parse_input(int ac, char **av)
{
	input_valid_check(av[1]);
	input_valid_check(av[2]);
	input_valid_check(av[3]);
	input_valid_check(av[4]);
	if (ac == 6)
		input_valid_check(av[5]);
}

int	check_ac(int ac)
{
	if (ac < 5 || ac > 6)
	{
		printf("argument input not correct! \n");
		return (-1);
	}
	return (0);
}

void	input_valid_check(char *str)
{
	int	len;

	len = 0;
	if (is_digit(str) == -1)
		printf("The input is not digit");
	while (str[len] != '\0')
		len++;
	if (len > 10)
		printf("The input is illegal");
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
			return (-1);
		while (s[i] != '\0')
		{
			if (s[i] < '0' && s[i] > '9')
				return (-1);
			i++;
		}
	}
	return (0);
}
