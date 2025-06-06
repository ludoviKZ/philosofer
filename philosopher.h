/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzorzit <lzorzit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:55:45 by lzorzit           #+#    #+#             */
/*   Updated: 2025/06/06 19:02:31 by lzorzit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include "philosopher.h"

typedef struct s_philosopher
{
	int					id;
	int					x_ate;
	int					left_fork_id;
	int					right_fork_id;
	long long			t_last_meal;
	struct s_prog		*program;
	pthread_t			thread_id;
}						t_philosopher;

typedef struct s_prog
{
	int					nb_philo;
	int					time_death;
	int					time_eat;
	int					time_sleep;
	int					n_eat;
	int					dieded;
	int					all_ate;
	long long			first_timestamp;
	pthread_mutex_t		meal_check;
	pthread_mutex_t		forks[250];
	pthread_mutex_t		writing;
	t_philosopher		philosophers[250];
}						t_prog;

void		*init_phil(void *philo_init);
int			init_mutex(t_prog *program);
int			init_philosophers(t_prog *program);
int			initprog(t_prog *program);
void		exit_launcher(t_prog *program, t_philosopher *philos);
void		death_checker(t_prog *r, t_philosopher *p);
void		smart_sleep(long long time, t_prog *program);
void		philo_eats(t_philosopher *philo);
long long	time_diff(long long past, long long pres);
long long	timestamp(void);
void		death(t_prog *prog, int i);
void		action_print(t_prog *program, int id, char *string);
long		atol(const char *str);
int			isnbr(char *matr);
void		asignval(t_prog *vals, long cpy, int i);
int			valid_assign(t_prog *vals, char **argv);
int			ft_isdigit(int str);
#endif 
