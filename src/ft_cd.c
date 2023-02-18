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
			{
				printf("ERREUR");
				exit (1);
			}
			else
				home = getcwd(NULL, 0);
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

	i = size_par(s);
	if (i == 1)
		g_home();
	else
	{
		old = getcwd(NULL, 0);
		change_old(old);
		if (chdir(s[1]) == -1)
			printf("No such file or directory\n");
		p = getcwd(NULL, 0);
		change_pwd(p);
	}
}
