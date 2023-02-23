/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlahyani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:40:26 by wlahyani          #+#    #+#             */
/*   Updated: 2023/02/23 18:40:30 by wlahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	handler(int sig)
{
	(void)sig;
	write (1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_free(char	**t)
{
	int	i;

	i = -1;
	while (t[++i])
		free (t[i]);
}

void	deallocate(t_list *list)
{
	t_list	*curr;
	t_list	*tmp;

	curr = list;
	while (curr)
	{
		free(curr->content);
		tmp = curr;
		curr = curr->next;
		free(tmp);
	}
}
