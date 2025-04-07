# include <philosofer.h>
# include "libft/libft.h"

int main(int argc, char **argv)
{
	t_vals	vals;
	t_program program;
	t_philo philo;
	if (argc != 5 && argc !=6)
		return(0);
	if (valid_assign(&vals, argv) == 0)
		return (0);
	initprog(&program, &philo);
	initphil(philo);

}