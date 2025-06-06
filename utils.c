/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzorzit <lzorzit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:47:03 by lzorzit           #+#    #+#             */
/*   Updated: 2025/06/06 19:02:24 by lzorzit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include "philosopher.h"

int	ft_isdigit(int str)
{
	if ((str >= '0') && (str <= '9'))
		return (1);
	return (0);
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	action_print(t_prog *program, int id, char *string)
{
	pthread_mutex_lock(&(program->writing));
	if (!(program->dieded))
	{
		printf("%lli ", timestamp() - program->first_timestamp);
		printf("%i ", id + 1);
		printf("%s\n", string);
	}
	pthread_mutex_unlock(&(program->writing));
	return ;
}
