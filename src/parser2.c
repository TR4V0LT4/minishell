/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlahyani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:38:37 by wlahyani          #+#    #+#             */
/*   Updated: 2023/02/23 15:38:40 by wlahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

int	lredirection_handler(t_list *tokens, t_parser *tmp)
{
	t_token	*curr;

	curr = (t_token *) tokens->content;
	if (curr->type == TOKEN_LREDIRECT)
	{
		tokens = tokens->next;
		curr = (t_token *) tokens->content;
		if (curr->type == TOKEN_STRING)
		{
			if (access(curr->value, F_OK) == 0)
				tmp->in_file = open(curr->value, O_RDWR);
			else
			{
				tmp->cmd[0] = "\0";
				if (tokens->next)
				{
					tokens = tokens->next;
					curr = (t_token *) tokens->content;
				}
				return (1);
			}
		}
	}
	return (0);
}

int	heredoc_and_append_handler(t_list **tokens, t_parser **tmp, int flag)
{
	t_token	*curr;

	curr = (t_token *)(*tokens)->content;
	if (curr->type == TOKEN_HEREDOC)
	{
		*tokens = (*tokens)->next;
		curr = (t_token *)(*tokens)->content;
		if (curr->type == TOKEN_STRING)
			(*tmp)->in_file = heredoc(curr->value, flag);
	}
	else if (curr->type == TOKEN_REDIRECT)
	{
		*tokens = (*tokens)->next;
		curr = (t_token *)(*tokens)->content;
		if (curr->type == TOKEN_STRING)
			(*tmp)->out_file = open(curr->value,
					O_TRUNC | O_CREAT | O_RDWR, 0664);
	}
	else
		return (1);
	return (0);
}

void	add_cmd_to_list(t_token *curr, t_list **cmd_list, t_parser **tmp)
{
	if (curr->type == TOKEN_PIPE)
	{
		ft_lstadd_back(cmd_list, ft_lstnew(*tmp));
		*tmp = init_content(*tmp);
	}
}

t_token	*go_next(t_list **tokens)
{
	t_token	*curr;

	curr = (t_token *)(*tokens)->content;
	if ((*tokens)->next)
	{
		*tokens = (*tokens)->next;
		curr = (t_token *)(*tokens)->content;
	}
	return (curr);
}
