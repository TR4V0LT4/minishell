/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhaliff <skhaliff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 23:48:31 by skhaliff          #+#    #+#             */
/*   Updated: 2023/02/23 00:09:13 by skhaliff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	remove_line(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-')
		i++;
	else
		return (0);
	while (s[i])
	{
		if (s[i] == 'n')
			i++;
		else
			break ;
	}
	if (s[i] == ' ' || s[i] == '\0')
		return (1);
	return (0);
}

void	ft_echo(char **s, int fd)
{
	int	i;
	int	remove_new_line;

	i = 1;
	remove_new_line = 0;
	while (s[i])
	{
		if (remove_line(s[1]))
		{
			remove_new_line = 1;
			i++;
		}
		if (!s[i])
			return ;
		ft_putstr_fd(s[i], fd);
		if (s[i + 1] != NULL)
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (!remove_new_line)
		printf("\n");
}
