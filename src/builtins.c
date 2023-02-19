/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhaliff <skhaliff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:05:46 by skhaliff          #+#    #+#             */
/*   Updated: 2023/02/19 16:33:03 by skhaliff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	builtins(t_list *list)
{
	t_parser	*d;

	d = (t_parser *)list->content;
	if (!ft_strncmp(d->cmd[0], "echo", 5))
		ft_echo(d->cmd);
	else if (!ft_strncmp(d->cmd[0], "cd", 3))
		ft_cd(d->cmd);
	else if (!ft_strncmp(d->cmd[0], "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(d->cmd[0], "export", 7))
		ft_export(d->cmd);
	else if (!ft_strncmp(d->cmd[0], "unset", 6))
		ft_unset(d->cmd);
	else if (!ft_strncmp(d->cmd[0], "env", 4))
		ft_env();
	else if (!ft_strncmp(d->cmd[0], "exit", 5))
		ft_exit(d->cmd);
	else
		return (1);
	return (0);
}

int	size_par(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_env(void)
{
	t_list	*curr;
	t_env	*curr_value;

	curr = g_data.env;
	while (curr)
	{
		curr_value = (t_env *)(curr->content);
		printf("%s=%s\n", curr_value->key, curr_value->value);
		curr = curr->next;
	}
}

void	ft_pwd(void)
{
	char	s[PATH_MAX];

	if (getcwd(s, sizeof(s)) != NULL)
		printf("%s\n", s);
}
