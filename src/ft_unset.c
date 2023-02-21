/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhaliff <skhaliff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:32:40 by skhaliff          #+#    #+#             */
/*   Updated: 2023/02/19 16:33:15 by skhaliff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	unset_utils(char **var, t_list *a, t_list *b, t_env *s)
{
	while (a)
	{
		s = (t_env *) a->content;
		if (!ft_strncmp(s->key, var[1], ft_strlen(var[1])))
		{
			if (a->next)
				b->next = a->next;
			else
				b->next = NULL;
			free(a);
			return ;
		}
		b = a;
		a = a->next;
	}
}

void	ft_unset(char **var)
{
	int		i;
	t_env	*temp_var;
	t_list	*previous;
	t_list	*a;

	i = 0;
	a = g_data.env;
	temp_var = s_malloc(sizeof(t_env));
	previous = NULL;
	i = size_par(var);
	if (i == 1)
		return ;
	else if (i == 2)
	{
		if (a->content == NULL)
			return ;
		unset_utils(var, a, previous, temp_var);
	}
}
