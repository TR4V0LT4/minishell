/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhaliff <skhaliff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:05:46 by skhaliff          #+#    #+#             */
/*   Updated: 2023/02/19 12:50:46 by skhaliff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	builtins(t_list *list)
{
	t_parser	*d;

	d = (t_parser *)list->content;
	if (!ft_strncmp(d->cmd[0], "echo", 5))
		echo(d->cmd);
	else if (!ft_strncmp(d->cmd[0], "cd", 3))
		ft_cd(d->cmd);
	else if (!ft_strncmp(d->cmd[0], "pwd", 4))
		pwd();
	else if (!ft_strncmp(d->cmd[0], "export", 7))
		ft_export(d->cmd);
	else if (!ft_strncmp(d->cmd[0], "unset", 6))
		unset(d->cmd);
	else if (!ft_strncmp(d->cmd[0], "env", 4))
		env();
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

void	unset(char **var)
{
	int		i;
	t_env	*temp_var;
	t_list	*previous;
	t_list	*a = g_data.env;

	i = 0;
	temp_var = malloc(sizeof(t_env));
	i = size_par(var);
	if (i == 1)
		return ;
	else if (i == 2)
	{
		if (a->content == NULL)
			return ;
		while (a)
		{
			temp_var = (t_env *) a->content;
			if (!ft_strncmp(temp_var->key, var[1], ft_strlen(var[1])))
			{
				if (a->next)
					previous->next = a->next;
				else
					previous->next = NULL;
				free(a);
				return ;
			}
			previous = a;
			a = a->next;
		}
	}
}

void	env(void)
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

void	pwd(void)
{
	char	s[PATH_MAX];

	if (getcwd(s, sizeof(s)) != NULL)
		printf("%s\n", s);
}

char	*get_new_env(char *s)
{
	t_env	*a;
	t_list	*l;
	int		i;

	i = ft_strlen(s);
	l = g_data.env;
	while (l)
	{
		a = (t_env *) l->content;
		if (ft_strncmp(s, a->key, i) == 0)
			return (a->value);
		l = l->next;
	}
	return (0);
}
