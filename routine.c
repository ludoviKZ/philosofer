
#include <philosopher.h>

void	smart_sleep(long long time, t_program *program)
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
	t_program	*program;

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
