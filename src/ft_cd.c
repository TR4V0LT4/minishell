/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhaliff <skhaliff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:46:16 by skhaliff          #+#    #+#             */
/*   Updated: 2023/02/23 00:23:59 by skhaliff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	change_pwd(char *home)
{
	t_list	*s;
	t_env	*a;

	s = g_data.env;
	while (s)
	{
		a = (t_env *) s->content;
		if (!ft_strncmp(a->key, "PWD", 3))
			a->value = home;
		s = s->next;
	}
}

void	change_old(char *old)
{
	t_list	*s;
	t_env	*a;

	s = g_data.env;
	while (s)
	{
		a = (t_env *) s->content;
		if (!ft_strncmp(a->key, "OLDPWD", 6))
			a->value = old;
		s = s->next;
	}
}

void	g_home(void)
{
	char	*home;
	char	*old;
	t_list	*a;
	t_env	*l;

	a = g_data.env;
	while (a)
	{
		l = (t_env *) a->content;
		if (!ft_strncmp(l->key, "HOME", 4))
		{
			old = getcwd(NULL, 0);
			change_old(old);
			if (chdir(l->value) == -1)
				printf("ERREUR");
			else
			{
				home = getcwd(NULL, 0);
				printf(">> %s\n", home);
			}
		}
		a = a->next;
	}
	change_pwd(home);
}

void	ft_cd(char **s)
{
	int		i;
	char	*p;
	char	*old;

	g_data.exit_status = 0;
	i = size_par(s);
	if (i == 1)
		g_home();
	else
	{
		old = getcwd(NULL, 0);
		change_old(old);
		if (chdir(s[1]) == -1)
		{
			printf("No such file or directory\n");
			g_data.exit_status = 1;
		}
		p = getcwd(NULL, 0);
		change_pwd(p);
	}
}
