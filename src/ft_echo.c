/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhaliff <skhaliff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 23:48:31 by skhaliff          #+#    #+#             */
/*   Updated: 2023/02/18 23:48:34 by skhaliff         ###   ########.fr       */
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

void	echo(char **s)
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
		printf("%s", s[i]);
		if (s[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (!remove_new_line)
		printf("\n");
}