/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhaliff <skhaliff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 23:47:49 by skhaliff          #+#    #+#             */
/*   Updated: 2023/02/22 00:42:34 by wlahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_export(t_list *export)
{
	t_env *temp_var;
	while (export)
	{
		temp_var = (t_env *)(export->content);
		printf("%s=%s\n", temp_var->key, temp_var->value);
		export = export->next;
	}
}

t_env * get_key_value(char *str)
{
	
	t_env *key_value;
	char *equal = ft_strchr(str, '=');

	if (equal == NULL)
		return NULL;

	*equal = '\0';
	key_value = malloc(sizeof(t_env));
	key_value->key = ft_strdup(str);
	key_value->value = ft_strdup(equal+1);

	return (key_value);
}

void replace_value(char *key, value, t_list *env);

void	ft_export(char **var)
{
	int		i;
	int 	j;
	t_env	*temp_var;
	t_list	*export;

	export = g_data.env;
	temp_var = s_malloc(sizeof(t_env));
	i = size_par(var);
	j = -1;

	if (i == 1)
		print_export(export);
	else
	{
		while (++j < i)
		{
			temp_var = get_key_value(var[j]);
			if (temp_var == NULL)
				continue;

			if (!ft_isalpha(temp_var->key[0]) && temp_var->key[0] != '_')
				printf("not a valid identifier\n");
			else
				ft_lstadd_back(&export, ft_lstnew(temp_var));
		}
	}
}
