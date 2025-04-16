#ifndef PHILOSOFER_H
#define PHILOSOFER_H

# include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
# include "libft/libft.h"

typedef	struct			s_philosopher
{
	int					id;
	int					x_ate;
	int					left_fork_id;
	int					right_fork_id;
	long long			t_last_meal;
	struct s_program		*program;
	pthread_t			thread_id;
}						t_philosopher;

typedef struct			s_program
{
	int					nb_philo;
	int					time_death;
	int					time_eat;
	int					time_sleep;
	int					nb_eat;
	int					dieded;
	int					all_ate;
	long long			first_timestamp;
	pthread_mutex_t		meal_check;
	pthread_mutex_t		forks[250];
	pthread_mutex_t		writing;
	t_philosopher		philosophers[250];
}						t_program;

void *init_phil(void *philo_init);
void initprog(t_program *program);
void	exit_launcher(t_program *program, t_philosopher *philos);
void	death_checker(t_program *r, t_philosopher *p);
void		smart_sleep(long long time, t_program *program);
void	philo_eats(t_philosopher *philo);
long long	time_diff(long long past, long long pres);
long long	timestamp(void);
void		action_print(t_program *program, int id, char *string);
long	atol(const char *str);
int	isnbr(char *matr);
void asignval(t_program *vals, long cpy, int i);
int valid_assign(t_program *vals, char **argv);


#endif 