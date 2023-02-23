/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhaliff <skhaliff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:46:32 by skhaliff          #+#    #+#             */
/*   Updated: 2023/02/23 17:11:50 by wlahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	par_number(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
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
	g_data.exit_status = 255;
	exit(g_data.exit_status);
}

void	one_parameter(char *s)
{
	int			a;
	long long	*b;

	b = malloc(sizeof(long long ));
	if (!par_number(s))
		not_number();
	else
	{
		a = ft_atoi(s, b);
		if (a == 0)
			not_number();
		else
		{
			g_data.exit_status = *b;
			write(1, "exit\n", 6);
			exit (g_data.exit_status % 256);
		}
	}
}

void	ft_exit(char **s)
{
	int	size;

	size = size_par(s);
	if (size == 1)
	{
		write(1, "exit\n", 6);
		exit(g_data.exit_status);
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
