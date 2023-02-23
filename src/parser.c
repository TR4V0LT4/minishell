/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhaliff <skhaliff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 22:10:00 by wlahyani          #+#    #+#             */
/*   Updated: 2023/02/23 14:39:45 by wlahyani         ###   ########.fr       */
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

t_list	*tokens_iteration(t_list *tokens, t_parser *tmp, int flag)
{
	t_token		*curr;

	curr = (t_token *) tokens->content;
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
	else if (!heredoc_and_append_handler(&tokens, &tmp, flag))
		;
	else if (lredirection_handler(tokens, tmp))
		printf("minishell: %s: No such file or directory\n", curr->value);
	return (tokens);
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
		tokens = tokens_iteration(tokens, tmp, flag);
		add_cmd_to_list(curr, &cmd_list, &tmp);
		curr = go_next(&tokens);
	}
	ft_lstadd_back(&cmd_list, ft_lstnew(tmp));
	return (cmd_list);
}

int	check_next(t_list *tokens)
{
	t_token	*curr;
	t_token	*next;

	curr = (t_token *) tokens->content;
	next = (t_token *) tokens->next->content;
	if (curr->type == TOKEN_PIPE && (next->type == TOKEN_REDIRECT
			|| next->type == TOKEN_LREDIRECT))
		curr = (t_token *) tokens->content;
	else if (curr->type == TOKEN_STRING)
	{
		if (quotes_checker(curr->value))
			return (1);
	}
	else if (curr->type != TOKEN_STRING && next->type != TOKEN_STRING)
		return (2);
	return (0);
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
		if (check_next(tokens) == 1)
			return (printf("minishell: syntax error unexpected token `\\n'\n"));
		else if (check_next(tokens) == 2)
			return (printf("minishell: syntax error unexpected token `%s'\n",
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
