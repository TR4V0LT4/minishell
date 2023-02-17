
#include "../include/minishell.h"

int builtins(t_list *list, t_list *envi)
{
	t_parser *d = (t_parser *)list->content;

	if(!ft_strncmp(d->cmd[0],"echo", 5))
		echo(d->cmd);
	else if(!ft_strncmp(d->cmd[0],"cd", 3)) 
		ft_cd(d->cmd, envi);
	else if(!ft_strncmp(d->cmd[0],"pwd", 4))
		pwd();
	else if(!ft_strncmp(d->cmd[0],"export", 7))
		ft_export(d->cmd, envi);
	else if(!ft_strncmp(d->cmd[0],"unset", 6))
		unset(d->cmd, envi);
	else if(!ft_strncmp(d->cmd[0],"env", 4))
		env(envi);
	else if(!ft_strncmp(d->cmd[0],"exit", 5))
		ft_exit(d->cmd);
	else 
		return 1;
	return 0;
}

void unset(char **var, t_list *envi)
{
	int	i = 0;
	//(void)var;
	t_env * temp_var;
	t_list *previous;

	temp_var = malloc(sizeof(t_env));
	i  = size_par(var);
	if (i == 1)
		return ;
	else if ( i == 2)
	{
	if (envi->content == NULL)
		return ;
	while (envi)
	{	
		temp_var = (t_env *) envi->content;
		if (!ft_strncmp(temp_var->key, var[1], ft_strlen(var[1])))
		{
			if (envi->next)
				previous->next = envi->next;
			else
				previous->next = NULL;
			free(envi);
			return ;
		}
		previous = envi;
		envi = envi->next;
	}
	}
}

void	env(t_list *senv)
{
	t_list *curr;
	t_env *curr_value;

	curr = senv;
	while (curr)
	{
		curr_value = (t_env *)(curr->content);
		printf("%s=%s\n", curr_value->key, curr_value->value);
		curr = curr->next;
	}
}

void	ft_export(char **var, t_list *env)
{
	int	i = 0;
	char	**all;
	t_env	*temp_var;
	t_list	*export = env;

	temp_var = malloc(sizeof(t_env));
	i = size_par(var);
	if (i == 1)
	{
		while (export)
		{
			temp_var = (t_env *)(export->content);
			printf("%s=%s\n", temp_var->key, temp_var->value);
			export = export->next;
		}
	}
	else
	{
		all = ft_split(var[1], '=');
		temp_var->key = all[0];
		temp_var->value = all[1];
		ft_lstadd_back(&export, ft_lstnew(temp_var));
	}
}

void	pwd(void)
{
	char s[PATH_MAX];
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

int	size_par(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	par_number(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	not_number()
{
	write(1, "numeric argument required\n", 27);
	exit(255);
}

void	one_parameter(char *s)
{
	int p;

	if (!par_number(s))
		not_number();
	else
	{
		p = ft_atoi(s);
		write(1, "exit\n", 6);
		exit (p % 256);
	}
}

void	ft_exit(char **s)
{
	int	size;

	size = size_par(s);
	if (size == 1)
	{
		write(1, "exit\n", 6);
		exit(0);
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

// char	*get_env_home(char **s)
// {
// 	int i = 0;
// 	char *home;

// 	home = NULL;
// 	while (s[i])
// 	{
// 		if (ft_strncmp(s[i], "HOME", ft_strlen("HOME")) == 0)
// 			home = ft_substr(s[i], 0, 4);
// 		i++;
// 	}
// 	return(home);
// }

void	change_env(t_list *l, char *home)
{
	t_list *s = l;
	t_env	*a;

	while (s)
	{
		a = (t_env *) s->content;
		if (!ft_strncmp(a->key, "PWD", 3) || !ft_strncmp(a->key, "OLDPWD", 6))
			a->value = home;
		s = s->next;
	}
}

void	g_home(t_list *env)
{
	//char	*s;
	char	*home;
	//int		i = 0;
	t_list *a = env;
	t_env	*l;
	//int		j = 0;

	while (a)
	{
		l = (t_env *) a->content;
		if (!ft_strncmp(l->key, "HOME", 4))
		{
			if (chdir(l->value) == -1)
			{
				printf("ERREUR");
				exit (1);
			}
			else
			{
				home = getcwd(NULL, 0);
			}
		}
		a = a->next;
		//i++;
	}
	change_env(env, home);
}

void	ft_cd(char **s, t_list *env)
{
	// int f = 0;
	int	i = 0;
	char	*p;
	// char **senv;
	// char **key;
	// t_list *a = env;
	// t_env	*l;
	//int j = 0;

	// key = malloc(4 * sizeof(char *));
	// senv = malloc(4 * sizeof(char *));
	// while (a)
	// {
	// 	l = (t_env *) a->content;
	// 	if (!ft_strncmp(l->key, "HOME", 4) || !ft_strncmp(l->key, "PWD", 3) || !ft_strncmp(l->key, "OLDPWD", 6))
	// 	{
	// 		key[f] = ft_strdup(l->key);
	// 		senv[j] = ft_strdup(l->value);
	// 		j++;
	// 		f++;
	// 	}
	// 	a = a->next;
	// }
	// senv[j] = NULL;
	// key[f] = NULL;
	i = size_par(s);
	if (i == 1)
		g_home(env);
	else
	{
		if (chdir(s[1]) == -1)
			printf("No such file or directory\n");
		p = getcwd(NULL, 0);
		change_env(env, p);
		// else
		// {
		// 	printf("ok\n");
		// }
	}
}
