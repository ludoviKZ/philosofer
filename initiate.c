# include <philosopher.h>
# include "libft/libft.h"

void	*init_phil(void *philo_init)
{
	int				i;
	t_philosopher	*philo;
	t_program		*program;

	i = 0;
	philo = (t_philosopher *)philo_init;
	program = philo->program;
	if (philo->id % 2)
		usleep(15000);
	while (!(program->dieded))
	{
		philo_eats(philo);
		if (program->all_ate)
			break ;
		action_print(program, philo->id, "is sleeping");
		smart_sleep(program->time_sleep, program);
		action_print(program, philo->id, "is thinking");
		i++;
	}
	return (NULL);
}

void	initprog(t_program *program)
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
		philo[i].t_last_meal = timestamp();
		n++;
	}
	death_checker(program, program->philosophers);
	exit_launcher(program, philo);
	return (0);
}
