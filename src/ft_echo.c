/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhaliff <skhaliff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 23:48:31 by skhaliff          #+#    #+#             */
/*   Updated: 2023/02/21 22:04:27 by wlahyani         ###   ########.fr       */
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
			return (1);
		i++;
	}
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
		
		ft_putstr_fd(s[i],fd);
		write(fd, "\n", 1);
	//	ft_putstr_fd("\0", fd);
		//printf("%s", s[i]);
		//if (s[i + 1] != NULL)
	//		printf(" ");
		i++;
	}
	if (!remove_new_line)
		printf("\n");
}
