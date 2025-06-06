/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzorzit <lzorzit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:47:00 by lzorzit           #+#    #+#             */
/*   Updated: 2025/06/06 19:01:35 by lzorzit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include "philosopher.h"

void	smart_sleep(long long time, t_prog *program)
{
	long long	i;

	i = timestamp();
	while (!(program->dieded))
	{
		if (time_diff(i, timestamp()) >= time)
			break ;
		usleep(50);
	}
}

void	philo_eats(t_philosopher *philo)
{
	t_prog	*program;

	program = philo->program;
	pthread_mutex_lock(&(program->forks[philo->left_fork_id]));
	action_print(program, philo->id, "has taken a fork");
	pthread_mutex_lock(&(program->forks[philo->right_fork_id]));
	action_print(program, philo->id, "has taken a fork");
	pthread_mutex_lock(&(program->meal_check));
	action_print(program, philo->id, "is eating");
	philo->t_last_meal = timestamp();
	pthread_mutex_unlock(&(program->meal_check));
	smart_sleep(program->time_eat, program);
	(philo->x_ate)++;
	pthread_mutex_unlock(&(program->forks[philo->left_fork_id]));
	pthread_mutex_unlock(&(program->forks[philo->right_fork_id]));
}
