/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzorzit <lzorzit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:46:55 by lzorzit           #+#    #+#             */
/*   Updated: 2025/07/14 15:42:18 by lzorzit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include "philosopher.h"

int	init_mutex(t_prog *program)
{
	int	i;

	i = 0;
	while (i < program->nb_philo)
	{
		if (pthread_mutex_init(&(program->forks[i]), NULL))
			return (0);
		if (pthread_mutex_init(&(program->x_ate[i]), NULL))
			return (0);
		if (pthread_mutex_init(&(program->last_ate[i]), NULL))
			return (0);
		i++;
	}
	if (pthread_mutex_init(&(program->writing), NULL))
		return (0);
	if (pthread_mutex_init(&(program->death), NULL))
		return (0);
	if (pthread_mutex_init(&(program->meal_check), NULL))
		return (0);
	return (1);
}

int	init_philosophers(t_prog *program)
{
	int	i;

	i = 0;
	while (i < program->nb_philo)
	{
		program->philosophers[i].id = i;
		program->philosophers[i].x_ate = 0;
		program->philosophers[i].left_fork_id = i;
		if (i == program->nb_philo - 1)
			program->philosophers[i].right_fork_id = 0;
		else
			program->philosophers[i].right_fork_id = (i + 1);
		program->philosophers[i].t_last_meal = 0;
		program->philosophers[i].program = program;
		i ++;
	}
	return (0);
}

void	*init_phil(void *philo_init)
{
	t_philosopher	*philo;
	t_prog			*program;

	philo = (t_philosopher *)philo_init;
	program = philo->program;
	if (program->nb_philo == 1)
	{
		smart_sleep(program->time_death);
		action_print(program, philo->id, "is thinking");
		return(0);
	}
	if (philo->id % 2)
		usleep(15000);
	pthread_mutex_lock(&(program->death));
	while (program->dieded < 1)
	{
		pthread_mutex_unlock(&(program->death));
		philo_eats(philo);
		action_print(program, philo->id, "is sleeping");
		smart_sleep(program->time_sleep);
		action_print(program, philo->id, "is thinking");
		pthread_mutex_lock(&(program->death));
	}
	pthread_mutex_unlock(&(program->death));
	return (0);
}

int	initprog(t_prog *program)
{
	int				n;
	t_philosopher	*philo;

	n = 0;
	philo = program->philosophers;
	program->first_timestamp = timestamp();
	while (n < program->nb_philo)
	{
		philo[n].t_last_meal = timestamp();
		if (pthread_create(&(philo[n].thread_id), NULL, init_phil, &(philo[n])))
			return (1);
		n++;
	}
	death_checker(program, program->philosophers);
	exit_launcher(program, philo);
	return (0);
}
