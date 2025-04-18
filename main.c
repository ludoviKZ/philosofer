#include <philosopher.h>
#include "libft/libft.h"

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
	initprog(&program);
	return (0);
}
