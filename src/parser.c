/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhaliff <skhaliff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 22:10:00 by wlahyani          #+#    #+#             */
/*   Updated: 2023/02/22 00:42:38 by wlahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

t_parser	*init_content(t_parser *content)
{
	content = (t_parser *)s_malloc(sizeof(t_parser));
	content->in_file = 0;
	content->out_file = 1;
	content->cmd = (char **)s_malloc(sizeof(char *) * 2);
	content->cmd[0] = NULL;
	content->cmd[1] = NULL;
	return (content);
}

t_list	*fill_command(t_list *tokens)
{
	t_list		*cmd_list;
	t_token		*curr;
	t_parser	*tmp;
	int			flag;

	flag = 0;
	tmp = NULL;
	cmd_list = NULL;
	tmp = init_content(tmp);
	parsing_quotes(tokens, &flag);
	curr = (t_token *) tokens->content;
	while (curr->type != TOKEN_EOF)
	{
		if (curr->type == TOKEN_STRING)
			tmp->cmd = realloc_cmd(tmp->cmd, curr->value);
		else if (curr->type == TOKEN_APPEND)
		{
			tokens = tokens->next;
			curr = (t_token *) tokens->content;
			if (curr->type == TOKEN_STRING)
				tmp->out_file = open(curr->value,
						O_CREAT | O_RDWR | O_APPEND, 0664);
		}
		else if (curr->type == TOKEN_HEREDOC)
		{
			tokens = tokens->next;
			curr = (t_token *) tokens->content;
			if (curr->type == TOKEN_STRING)
				tmp->in_file = heredoc(curr->value, flag);
		}
		else if (curr->type == TOKEN_REDIRECT)
		{
			tokens = tokens->next;
			curr = (t_token *) tokens->content;
			if (curr->type == TOKEN_STRING)
				tmp->out_file = open(curr->value,
						O_TRUNC | O_CREAT | O_RDWR, 0664);
		}
		else if (curr->type == TOKEN_LREDIRECT)
		{
			tokens = tokens->next;
			curr = (t_token *) tokens->content;
			if (curr->type == TOKEN_STRING)
			{
				if (access(curr->value, F_OK) == 0)
					tmp->in_file = open(curr->value, O_RDWR);
				else
				{
					printf("minishell: %s: No such file or directory\n",
						curr->value);
					tmp->cmd[0] = "\0";
					if (tokens->next)
					{
						tokens = tokens->next;
						curr = (t_token *) tokens->content;
					}
				}
			}
		}
		else if (curr->type == TOKEN_PIPE)
		{
			ft_lstadd_back(&cmd_list, ft_lstnew(tmp));
			tmp = init_content(tmp);
		}
		if (tokens->next)
		{
			tokens = tokens->next;
			curr = (t_token *) tokens->content;
		}
	}
	ft_lstadd_back(&cmd_list, ft_lstnew(tmp));
	return (cmd_list);
}

int	check_syntax(t_list *tokens)
{
	t_token	*curr;
	t_token	*next;

	curr = (t_token *) tokens->content;
	next = (t_token *) tokens->next->content;
	if (curr->type == TOKEN_PIPE)
		return (printf("minishell: syntax error unexpected token `|'\n"));
	while (curr->type != TOKEN_EOF)
	{
		if (curr->type == TOKEN_PIPE && (next->type == TOKEN_REDIRECT
				|| next->type == TOKEN_LREDIRECT))
		{
			curr = (t_token *) tokens->content;
			next = (t_token *) tokens->next->content;
		}
		else if (curr->type == TOKEN_STRING)
		{
			if (quotes_checker(curr->value))
				return (printf(
						"minishell: syntax error unexpected token `\\n'\n"));
		}
		else if (curr->type != TOKEN_STRING && next->type != TOKEN_STRING)
			return (printf(
					"minishell: syntax error unexpected token `%s'\n",
					next->value));
		tokens = tokens->next;
		curr = (t_token *) tokens->content;
		if (curr->type != TOKEN_EOF)
			next = (t_token *) tokens->next->content;
	}
	if (curr->type == TOKEN_REDIRECT)
		return (printf(
				"minishell: syntax error near unexpected token `newline'\n"));
	return (0);
}
