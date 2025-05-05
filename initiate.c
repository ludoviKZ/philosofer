
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include "philosopher.h"
#include "libft/libft.h"

void	*init_phil(void *philo_init)
{
	t_philosopher	*philo;
	t_program		*program;

	philo = (t_philosopher *)philo_init;
	program = philo->program;
	if (philo->id % 2)
		usleep(15000);
	if (program->nb_philo == 1)
	{
		action_print(program, philo->id, "is thinking");
		while (!(program->dieded))
			smart_sleep(program->time_sleep, program);
		return(0);
	}
	while (!(program->dieded))
	{
		philo_eats(philo);
		if (program->all_ate)
			break ;
		action_print(program, philo->id, "is sleeping");
		smart_sleep(program->time_sleep, program);
		action_print(program, philo->id, "is thinking");
	}
	return(0);
}

int	initprog(t_program *program)
{
	int				n;
	t_philosopher	*philo;

	n = 0;
	philo = program->philosophers;
	program->first_timestamp = timestamp();
	while (n < program->nb_philo)
	{
		if (pthread_create(&(philo[n].thread_id), NULL, init_phil, &(philo[n])))
			return (1);
		philo[n].t_last_meal = timestamp();
		n++;
	}
	death_checker(program, program->philosophers);
	exit_launcher(program, philo);
	return (0);
}
