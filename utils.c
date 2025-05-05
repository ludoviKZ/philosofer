# include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include "philosopher.h"

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	action_print(t_program *program, int id, char *string)
{
	pthread_mutex_lock(&(program->writing));
	if (!(program->dieded))
	{
		printf("%lli ", timestamp() - program->first_timestamp);
		printf("%i ", id + 1);
		printf("%s\n", string);
	}
	pthread_mutex_unlock(&(program->writing));
	return ;
}
