/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzorzit <lzorzit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:47:00 by lzorzit           #+#    #+#             */
/*   Updated: 2025/07/14 15:46:12 by lzorzit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include "philosopher.h"

void	smart_sleep(long long time)
{
	long long	i;

	i = timestamp();
	while (time_diff(i, timestamp()) < time)
		usleep(50);
}

void	anti_deadlock_mut(t_philosopher *philo, int leftf, int rightf)
{
	t_prog	*program;

	program = philo->program;
	if (leftf % 2 == 0 && rightf % 2 == 0)
	{
		pthread_mutex_lock(&(program->forks[rightf]));
		action_print(program, philo->id, "has taken a fork");
		pthread_mutex_lock(&(program->forks[leftf]));
		action_print(program, philo->id, "has taken a fork");
	}
	else if (leftf % 2 == 0)
	{
		pthread_mutex_lock(&(program->forks[leftf]));
		action_print(program, philo->id, "has taken a fork");
		pthread_mutex_lock(&(program->forks[rightf]));
		action_print(program, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&(program->forks[rightf]));
		action_print(program, philo->id, "has taken a fork");
		pthread_mutex_lock(&(program->forks[leftf]));
		action_print(program, philo->id, "has taken a fork");
	}
}

void	philo_eats(t_philosopher *philo)
{
	t_prog	*program;

	program = philo->program;
	anti_deadlock_mut(philo, philo->left_fork_id, philo->right_fork_id);
	pthread_mutex_lock(&(program->meal_check));
	pthread_mutex_lock(&(program->last_ate[philo->id]));
	action_print(program, philo->id, "is eating");
	philo->t_last_meal = timestamp();
	pthread_mutex_unlock(&(program->meal_check));
	pthread_mutex_unlock(&(program->last_ate[philo->id]));
	pthread_mutex_lock(&(program->x_ate[philo->id]));
	(philo->x_ate)++;
	pthread_mutex_unlock(&(program->x_ate[philo->id]));
	smart_sleep(program->time_eat);
	pthread_mutex_unlock(&(program->forks[philo->left_fork_id]));
	pthread_mutex_unlock(&(program->forks[philo->right_fork_id]));
}
