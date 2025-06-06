/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzorzit <lzorzit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:47:06 by lzorzit           #+#    #+#             */
/*   Updated: 2025/06/06 19:01:41 by lzorzit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include "philosopher.h"

long	atol(const char *str)
{
	long	result;
	int		neg;

	result = 0;
	neg = 1;
	while (*str == '\f' || *str == '\n' || *str == '\r' || *str == '\t'
		|| *str == '\v' || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result *= 10;
		result += *str - '0';
		str++;
	}
	return (result * neg);
}

int	isnbr(char *matr)
{
	int	i;

	i = 0;
	if (!matr[i])
		return (0);
	while (matr[i])
	{
		if (ft_isdigit(matr[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	asignval(t_prog *vals, long cpy, int i)
{
	if (i == 1)
		vals->nb_philo = cpy;
	else if (i == 2)
		vals->time_death = cpy;
	else if (i == 3)
		vals->time_eat = cpy;
	else if (i == 4)
		vals->time_sleep = cpy;
	else if (i == 5)
		vals->n_eat = cpy;
}

int	valid_assign(t_prog *vals, char **argv)
{
	int		i;
	long	cpy;

	cpy = 0;
	i = 1;
	while (argv[i] != 0)
	{
		if (isnbr(argv[i]) == 0)
			return (0);
		cpy = atol(argv[i]);
		if (cpy > 2147483647)
			return (0);
		asignval(vals, cpy, i);
		i++;
	}
	if (!argv[5])
	{
		vals->n_eat = -1;
	}
	vals->all_ate = 0;
	vals->dieded = 0;
	return (1);
}
