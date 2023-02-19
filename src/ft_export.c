/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhaliff <skhaliff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 23:47:49 by skhaliff          #+#    #+#             */
/*   Updated: 2023/02/19 00:04:21 by skhaliff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	}
}
