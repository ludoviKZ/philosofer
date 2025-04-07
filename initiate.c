# include <philosofer.h>
# include "libft/libft.h"

void	init_philos(t_program *prog, t_philo *philo, t_vals val)
{
	int	i;

	i = -1;
	while (++i < atol(argv[1]))
	{
		philo[i].id = i + 1;
		philo[i].times.die = ft_atoi(argv[2]);
		philo[i].times.eat = ft_atoi(argv[3]);
		philo[i].times.sleep = ft_atoi(argv[4]);
		philo[i].times.last_meal = get_current_time();
		philo[i].times.born_time = get_current_time();
		philo[i].must_eat = -1;
		if (argv[5])
			philo[i].must_eat = ft_atoi(argv[5]);
		philo[i].meals_eaten = 0;
		philo[i].philo_count = ft_atoi(argv[1]);
		philo[i].mutexes.left_fork = &forks[i];
		if (i == 0)
			philos[i].mutexes.right_fork = &forks[philos[i].philo_count - 1];
		else
			philos[i].mutexes.right_fork = &forks[i - 1];
		philos[i].mutexes.write_lock = &en->write_lock;
		philos[i].mutexes.meal_lock = &en->meal_lock;
	}
}
void	initlocks(t_program *program, int count)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			destroy_all(program, "[Mutex Init ERROR]\n", i, 1);
	}
}

void initprog(t_program *program, t_philo *philo)
{
	program->philos = philo;
	program->dead_flag = philo->dead;
	program->dead_lock = philo->dead_lock;
	program->meal_lock = philo->meal_lock;
	program->write_lock = philo->write_lock;
	if (pthread_mutex_init(&program->write_lock, NULL) != 0
	|| pthread_mutex_init(&program->meal_lock, NULL) != 0)
		destroy_all(program, "[Mutex Init ERROR]\n", -1, 1);
}