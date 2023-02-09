/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yomari <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 03:35:35 by yomari            #+#    #+#             */
/*   Updated: 2023/01/26 08:23:40 by wlahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

int builtins(t_list *list, t_list *envi)
{
	t_parser *curr = (t_parser *)list->content;
	

	if(!ft_strncmp(curr->cmd[0],"echo",4)) 
		env(envi);
	else if(!ft_strncmp(curr->cmd[0],"cd",2)) 
		env(envi);
	else if(!ft_strncmp(curr->cmd[0],"pwd",3))
		printf("khas yt9ad hadshi");
	else if(!ft_strncmp(curr->cmd[0],"export",6))
		export(curr->cmd[1],envi);
	else if(!ft_strncmp(curr->cmd[0],"unset",5))
		unset(curr->cmd[1] ,envi);
	else if(!ft_strncmp(curr->cmd[0],"env",3))
		env(envi);
	else if(!ft_strncmp(curr->cmd[0],"exit",4)) 
		env(envi);
	else 
		return 1;
	return 0;
}

void unset(char *var, t_list *envi)
{
	(void)var;
	t_env * temp_var;
	temp_var = malloc(sizeof(t_env));
	t_list *previous ;
	while(envi)
	{	
		temp_var = (t_env *) envi->content;
		if(!ft_strncmp(temp_var->key,var,ft_strlen(var)))
		{
			if(envi->next)
				previous->next = envi->next;
			else
				previous->next = NULL;
			free(envi);
			return ;
		}
		previous  = envi;
		envi = envi->next;
	}
}
void	env(t_list* senv)
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

void	export(char *var , t_list *env)
{	
	char **all;
	t_env * temp_var;
	temp_var = malloc(sizeof(t_env));
	all = ft_split(var, '=');
	temp_var->key = all[0];
	temp_var->value= all[1];
	ft_lstadd_back(&env, ft_lstnew(temp_var));

}



