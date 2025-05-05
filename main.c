#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include "philosopher.h"
#include "libft/libft.h"

int	init_mutex(t_program *program)
{
	int i;

	i = program->nb_philo;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(program->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(program->writing), NULL))
		return (1);
	if (pthread_mutex_init(&(program->meal_check), NULL))
		return (1);
	return (0);
}

int	init_philosophers(t_program *program)
{
	int i;

	i = program->nb_philo;
	while (--i >= 0)
	{
		program->philosophers[i].id = i;
		program->philosophers[i].x_ate = 0;
		program->philosophers[i].left_fork_id = i;
		program->philosophers[i].right_fork_id = (i + 1) % program->nb_philo;
		program->philosophers[i].t_last_meal = 0;
		program->philosophers[i].program = program;
	}
	return (0);
}


void	exit_launcher(t_program *program, t_philosopher *philos)
{
	int	i;

	i = -1;
	while (++i < program->nb_philo)
		pthread_join(philos[i].thread_id, NULL);
	i = -1;
	while (++i < program->nb_philo)
		pthread_mutex_destroy(&(program->forks[i]));
	pthread_mutex_destroy(&(program->writing));
}

void	death_checker(t_program *r, t_philosopher *p)
{
	int	i;

	while (!(r->all_ate))
	{
		i = -1;
		while (++i < r->nb_philo && !(r->dieded))
		{
			pthread_mutex_lock(&(r->meal_check));
			if (time_diff(p[i].t_last_meal, timestamp()) > r->time_death)
			{
				action_print(r, i, "died");
				r->dieded = 1;
			}
			pthread_mutex_unlock(&(r->meal_check));
			usleep(100);
		}
		if (r->dieded)
			break ;
		i = 0;
		while (r->nb_eat != -1 && i < r->nb_philo && p[i].x_ate >= r->nb_eat)
			i++;
		if (i == r->nb_philo)
			r->all_ate = 1;
	}
}

int	main(int argc, char **argv)
{
	t_program	program;


	if (argc != 5 && argc != 6)
		return (0);
	if (valid_assign(&program, argv) == 0)
		return (0);
	if (init_mutex(&program))
		return (2);
	init_philosophers(&program);
	if (initprog(&program) == 1)
		return (0);
	return (0);
}
