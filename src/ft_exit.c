#include "../include/minishell.h"

int	par_number(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	not_number(void)
{
	write(1, "numeric argument required\n", 27);
	exit(255);
}

void	one_parameter(char *s)
{
	int	p;

	if (!par_number(s))
		not_number();
	else
	{
		p = ft_atoi(s);
		write(1, "exit\n", 6);
		exit (p % 256);
	}
}

void	ft_exit(char **s)
{
	int	size;

	size = size_par(s);
	if (size == 1)
	{
		write(1, "exit\n", 6);
		exit(0);
	}
	else if (size == 2)
		one_parameter(s[1]);
	else
	{
		if (!par_number(s[1]))
			not_number();
		write(1, "too many arguments\n", 20);
	}
}
