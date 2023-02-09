/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlahyani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 22:10:00 by wlahyani          #+#    #+#             */
/*   Updated: 2023/02/02 22:33:13 by wlahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_parser	*init_content(t_parser *content)
{
	content = (t_parser *)malloc(sizeof(t_parser));
	//content->in_fd = NULL;
	//content->out_fd = NULL;
	content->cmd = (char **)malloc(sizeof(char *) * 2);
	content->cmd[0] = NULL;
	content->cmd[1] = NULL;
	return (content);
}

void	heredoc(t_list *tokens)
{
	char		*str;
	char		*path;
	int			pid;
	t_token		*curr;
	int			fd;

	fd = 1;
	curr = (t_token *) tokens->content;
	while (curr->type != TOKEN_EOF)
	{
		if (curr->type == TOKEN_HEREDOC)
		{
			tokens = tokens->next;
			curr = (t_token *) tokens->content;
			if (curr->type == TOKEN_STRING)
			{
				pid = fork();
				if (pid == 0)
				{
					path = ft_strjoin("/tmp/", curr->value);
					fd = open(path, O_CREAT | O_RDWR | O_APPEND, 0664);
					while (ft_strncmp(str, curr->value, ft_strlen(curr->value) + 1))
					{
						str = readline(">");
						if (ft_strncmp(str, curr->value, ft_strlen(curr->value) + 1))
						{
							write(fd, str, ft_strlen(str));
							write(fd, "\n", 1);
						}
					}
					write(fd, "\0", 1);
					close(fd);
					exit(1);
				}
				else
					wait(NULL);
			}
		}
		tokens = tokens->next;
		curr = (t_token *) tokens->content;
	}
}

t_list	*fill_command(t_list *tokens)
{
	t_list		*cmd_list;
	t_token		*curr;
	t_parser	*tmp;

	tmp = NULL;
	cmd_list = NULL;
	tmp = init_content(tmp);
	curr = (t_token *) tokens->content;
	heredoc(tokens);
	while (curr->type != TOKEN_EOF)
	{
		if (curr->type == TOKEN_STRING)
			tmp->cmd = realloc_cmd(tmp->cmd, curr->value);
		else if (curr->type == TOKEN_APPEND)
		{
			tokens = tokens->next;
			curr = (t_token *) tokens->content;
			if (curr->type == TOKEN_STRING)
				tmp->out_fd = ft_strdup(curr->value);
		}
		else if (curr->type == TOKEN_REDIRECT)
		{
			tokens = tokens->next;
			curr = (t_token *) tokens->content;
			if (curr->type == TOKEN_STRING)
				tmp->out_fd = ft_strdup(curr->value);
		}
		else if (curr->type == TOKEN_LREDIRECT)
		{
			tokens = tokens->next;
			curr = (t_token *) tokens->content;
			if (curr->type == TOKEN_STRING)
				tmp->in_fd = ft_strdup(curr->value);
		}
		else if (curr->type == TOKEN_PIPE)
		{
			ft_lstadd_back(&cmd_list, ft_lstnew(tmp));
			tmp = init_content(tmp);
		}
		tokens = tokens->next;
		curr = (t_token *) tokens->content;
	}
	ft_lstadd_back(&cmd_list, ft_lstnew(tmp));
	return (cmd_list);
}

char	*string_parser(char *str)
{
	int		i;
	char	*string;
	char 	*var;

	i = 0;
	string = NULL;
	var = NULL;

	// "" error
	while (str[i])
	{
		if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
			{
				string = append_to_str(string, str[i]);
				i++;
			}
			if (str[i] == '\0')
				return (NULL);
			i++;
		}
		else if (str[i] == '\'')
		{	
			i++;
			while (str[i] && str[i] != '\'')
			{
				string = append_to_str(string, str[i]);
				i++;
			}
			if (str[i] == '\0')
				return (NULL);
			i++;
		}
		else
		{
			string = append_to_str(string, str[i]);
			i++;
		}
	}
	return (string);
}

int	check_syntax(t_list *tokens)
{
	t_token	*curr;
	t_token	*next;
	char	*temp_value;
	char	*str;

	curr = (t_token *) tokens->content;
	next = (t_token *) tokens->next->content;
	if (curr->type == TOKEN_PIPE)
		return (printf("minishell: syntax error unexpected token `|'\n"));
	while (curr->type != TOKEN_EOF)
	{
		if (curr->type == TOKEN_PIPE && next->type == TOKEN_REDIRECT)
		{
			curr = (t_token *) tokens->content;
			next = (t_token *) tokens->next->content;
		}
		else if (curr->type == TOKEN_STRING)
		{
			temp_value = curr->value;
			str = string_parser(curr->value);
			if (str == NULL)
				return (printf("minishell: syntax error unexpected token `\\n'\n"));
			if (str != temp_value)
				free(temp_value);
			curr->value = str;
		}
		else if (curr->type != TOKEN_STRING && next->type != TOKEN_STRING)
			return (printf("minishell: syntax error unexpected token `%s'\n", next->value));
		tokens = tokens->next;
		curr = (t_token *) tokens->content;
		if (curr->type != TOKEN_EOF)
			next = (t_token *) tokens->next->content;
	}
	if (curr->type == TOKEN_REDIRECT)
		return (printf("minishell: syntax error near unexpected token `newline'\n"));
	return (0);
}
