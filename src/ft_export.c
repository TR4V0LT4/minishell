/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhaliff <skhaliff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 23:47:49 by skhaliff          #+#    #+#             */
/*   Updated: 2023/02/23 00:18:45 by skhaliff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_export(t_list *export)
{
	t_env	*temp_var;

	while (export)
	{
		temp_var = (t_env *)(export->content);
		printf("declare -x %s", temp_var->key);
		if (temp_var->value)
			printf("=\"%s\"", temp_var->value);
		printf("\n");
		export = export->next;
	}
}

t_env	*get_key_value(char *str)
{
	t_env	*key_value;
	char	*equal;

	equal = ft_strchr(str, '=');
	// if (equal == NULL)
	// 	return (NULL);
	if (equal != NULL)
		*equal = '\0';
	key_value = s_malloc(sizeof(t_env));
	key_value->key = ft_strdup(str);
	if (equal != NULL)
		key_value->value = ft_strdup(equal + 1);
	else
		key_value->value = NULL;
	return (key_value);
}

int	replace_value(char *key, char *value, t_list *env)
{
	t_env	*s;

	while (env)
	{
		s = (t_env *) env->content;
		if (!ft_strcmp(key, s->key) && (s->value != NULL))
		{
			s->value = value;
			return (1);
		}
		env = env->next;
	}
	return (0);
}

int	check_key(char *key, t_list *env)
{
	t_env	*s;

	while (env)
	{
		s = (t_env *) env->content;
		if (!ft_strcmp(key, s->key))
			return (1);
		env = env->next;
	}
	return (0);
}

void	ft_export(char **var)
{
	int		i;
	int		j;
	int		s;
	t_env	*temp_var;
	t_list	*export;

	export = g_data.env;
	temp_var = s_malloc(sizeof(t_env));
	i = size_par(var);
	j = 0;
	s = 0;
	if (i == 1)
		print_export(export);
	else
	{
		while (++j < i)
		{
			temp_var = get_key_value(var[j]);
			// printf("||| %s\n", temp_var->key);
			// printf("||| %s\n", temp_var->value);
			// if (temp_var == NULL)
			// 	continue ;
			s = replace_value(temp_var->key, temp_var->value, export);
			int b = check_key(temp_var->key, export);
			if (!ft_isalpha(temp_var->key[0]) && temp_var->key[0] != '_')
				printf("not a valid identifier\n");
			if (s == 0 && b == 0)
				ft_lstadd_back(&export, ft_lstnew(temp_var));
		}
	}
}
