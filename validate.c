# include <philosofer.h>
# include "libft/libft.h"

long	atol(const char *str)
{
	long	result;
	int	neg;

	result = 0;
	neg = 1;
	while (*str == '\f' || *str == '\n' || *str == '\r' || *str == '\t'
		|| *str == '\v' || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result *= 10;
		result += *str - '0';
		str++;
	}
	return (result * neg);
}

int	isnbr(char *matr)
{
	int	i;

	i = 0;
	if (!matr[i])
		return(0);
	while (matr[i])
	{
		if (ft_isdigit(matr[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
void asignval(t_vals *vals, long cpy, int i)
{
	if(i == 2)
		vals->philo = cpy;
	else if(i == 3)
		vals->die = cpy;
	else if(i == 4)
		vals->eat = cpy;	
	else if(i == 5)
		vals->sleep = cpy;	
	else if(i == 6)
		vals->reps = cpy;	
}
int valid_assign(t_vals *vals, char **argv)
{
	int		i;
	long cpy;
	
	cpy = 0;
	i = 2;
	while (argv[i] != 0)
	{
		if (isnbr(argv[i]) == 0)
			return (0);
		cpy = ft_atol(argv[i]);
		if (cpy > 2147483647)
			return (0);
		asignval(vals, cpy, i);
		i++;
	}
	return (1);
}