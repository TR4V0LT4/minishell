/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhaliff <skhaliff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:05:46 by skhaliff          #+#    #+#             */
/*   Updated: 2023/02/18 18:24:32 by skhaliff         ###   ########.fr       */
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

void unset(char **var)
{
	int	i = 0;
	t_env * temp_var;
	t_list *previous;

	temp_var = malloc(sizeof(t_env));
	i = size_par(var);
	if (i == 1)
		return ;
	else if (i == 2)
	{
	if (g_data.env->content == NULL)
		return ;
	while (g_data.env)
	{	
		temp_var = (t_env *) g_data.env->content;
		if (!ft_strncmp(temp_var->key, var[1], ft_strlen(var[1])))
		{
			if (g_data.env->next)
				previous->next = g_data.env->next;
			else
				previous->next = NULL;
			free(g_data.env);
			return ;
		}
		previous = g_data.env;
		g_data.env = g_data.env->next;
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

void	print_export(t_list *export, t_env *temp_var)
{
	while (export)
	{
		temp_var = (t_env *)(export->content);
		printf("%s=%s\n", temp_var->key, temp_var->value);
		export = export->next;
	}
}

void	ft_export(char **var)
{
	int		i;
	char	**all;
	t_env	*temp_var;
	t_list	*export;

	export = g_data.env;
	temp_var = malloc(sizeof(t_env));
	i = size_par(var);
	if (i == 1)
		print_export(export, temp_var);
	else
	{
		all = ft_split(var[1], '=');
		temp_var->key = all[0];
		temp_var->value = all[1];
		if (!ft_isalpha(temp_var->key[0]) && temp_var->key[0] != '_')
			printf("not a valid identifier\n");
		else
			ft_lstadd_back(&export, ft_lstnew(temp_var));
		//free(temp_var);
	}
}

void	pwd(void)
{
	char	s[PATH_MAX];

	if (getcwd(s, sizeof(s)) != NULL)
		printf("%s\n", s);
}

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
