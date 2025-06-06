/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzorzit <lzorzit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:46:57 by lzorzit           #+#    #+#             */
/*   Updated: 2025/06/06 18:45:03 by lzorzit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include "philosopher.h"
#include "libft/libft.h"

void	exit_launcher(t_prog *program, t_philosopher *philos)
{
	int	i;

	i = 0;
	while (i < program->nb_philo)
	{
		pthread_join(philos[i].thread_id, NULL);
		i ++;
	}
	i = 0;
	while (i < program->nb_philo)
	{
		pthread_mutex_destroy(&(program->forks[i]));
		i++;
	}
	pthread_mutex_destroy(&(program->writing));
}

void	death(t_prog *prog, int i)
{
	action_print(prog, i, "died");
	prog->dieded = 1;
}

void	death_checker(t_prog *prog, t_philosopher *phil)
{
	int	i;

	while (!(prog->all_ate))
	{
		i = 0;
		while (i < prog->nb_philo && !(prog->dieded))
		{
			pthread_mutex_lock(&(prog->meal_check));
			if (time_diff(phil[i].t_last_meal, timestamp()) > prog->time_death)
				death(prog, i);
			pthread_mutex_unlock(&(prog->meal_check));
			usleep(100);
			i++;
		}
		if (prog->dieded)
			break ;
		i = 0;
		while (prog->n_eat != -1 && i < prog->nb_philo
			&& phil[i].x_ate >= prog->n_eat)
			i++;
		if (i == prog->nb_philo)
			prog->all_ate = 1;
	}
}

int	main(int argc, char **argv)
{
	t_prog	program;

	if (argc != 5 && argc != 6)
		return (0);
	if (valid_assign(&program, argv) == 0)
		return (0);
	if (init_mutex(&program) == 0)
		return (0);
	init_philosophers(&program);
	if (initprog(&program) == 1)
		return (0);
	return (0);
}
