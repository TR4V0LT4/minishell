/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlahyani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 22:10:00 by wlahyani          #+#    #+#             */
/*   Updated: 2023/02/19 16:44:30 by wlahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_parser	*init_content(t_parser *content)
{
	content = (t_parser *)malloc(sizeof(t_parser));
	content->in_file = 0;
	content->out_file = 1;
	content->cmd = (char **)malloc(sizeof(char *) * 2);
	content->cmd[0] = NULL;
	content->cmd[1] = NULL;
	return (content);
}
void heredoc_signals()
{
	exit(0);
}
int	heredoc(char *value)
{
	char		*str;
	char		*path;
	int			pid;
	int			fd;

	path = ft_strjoin("/tmp/", "minishell");
	fd = open(path, O_CREAT  | O_WRONLY, 0600 );
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, heredoc_signals);
		signal(SIGQUIT, SIG_IGN);
		
		while (ft_strncmp(str, value, ft_strlen(value) + 1))
		{
			if(*str == '\0')
			exit(0);
			if(str == NULL)
				exit(0);
			str = readline(">");
			//str = string_parser(str);
			if (ft_strncmp(str, value, ft_strlen(value) + 1) )
			{
				write(fd, str, ft_strlen(str));
				write(fd, "\n", 1);
			}
			else 
				exit(0);
		}
		write(fd, "\0", 1);
		close(fd);
	}
	else
		wait(NULL);
	close(fd);
	fd = open(path, O_RDONLY);
	return fd;
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
	while (curr->type != TOKEN_EOF)
	{
		if (curr->type == TOKEN_STRING)
			tmp->cmd = realloc_cmd(tmp->cmd, curr->value);
		else if (curr->type == TOKEN_APPEND)
		{
			tokens = tokens->next;
			curr = (t_token *) tokens->content;
			if (curr->type == TOKEN_STRING)
				tmp->out_file = open(curr->value, O_CREAT | O_RDWR | O_APPEND, 0664);
		}
		else if (curr->type == TOKEN_HEREDOC)
		{
			tokens = tokens->next;
			curr = (t_token *) tokens->content;
			if (curr->type == TOKEN_STRING)
				tmp->in_file = heredoc(curr->value);
		}
		else if (curr->type == TOKEN_REDIRECT)
		{
			tokens = tokens->next;
			curr = (t_token *) tokens->content;
			if (curr->type == TOKEN_STRING)
				tmp->out_file = open(curr->value, O_TRUNC | O_CREAT | O_RDWR, 0664);
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
					printf("im here\n");
					printf("minishell: %s: NO such file or directory\n", curr->value);
					tmp->cmd[0] = "\0";
					if(tokens->next)
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
		if(tokens->next)
		{
			tokens = tokens->next;
			curr = (t_token *) tokens->content;
		}
	}
	ft_lstadd_back(&cmd_list, ft_lstnew(tmp));
	return (cmd_list);
}

char	*string_parser(char *str)
{
	int		i;
	char *string;
	i = 0;
	string = NULL;
	char *var_name;

	// "" error
	while (str[i])
	{
		if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
			{
				if (str[i] == '$')
				{
					var_name = get_var_name(str+i);
					string = expand(string, var_name);
					i += ft_strlen(var_name);
					free(var_name);
				}
				else
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
				if (str[i + 1] == '?')
					printf("%d\n", g_data.exit_status);
				string = append_to_str(string, str[i]);
				i++;
			}
			if (str[i] == '\0')
				return (NULL);
			i++;
		}
		else
		{
			if (str[i] == '$')
			{
				var_name = get_var_name(str+i);
				string = expand(string, var_name);
				i += ft_strlen(var_name);
				free(var_name);
			}
			else
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
	else if(curr->type == TOKEN_STRING)
	{
			temp_value = curr->value;
			str = string_parser(curr->value);
			if (str == NULL)
				return (printf("minishell: syntax error unexpected token `\\n'\n"));
			if (str != temp_value)
				free(temp_value);
			curr->value = str;
	}
	while (curr->type != TOKEN_EOF)
	{
		if (curr->type == TOKEN_PIPE && (next->type == TOKEN_REDIRECT  || next->type == TOKEN_LREDIRECT))
		{
			curr = (t_token *) tokens->content;
			next = (t_token *) tokens->next->content;
		}
		else if (curr->type != TOKEN_HEREDOC && next->type == TOKEN_STRING)
		{
			temp_value = next->value;
			str = string_parser(next->value);
			if (str == NULL)
				return (printf("minishell: syntax error unexpected token `\\n'\n"));
			if (str != temp_value)
				free(temp_value);
			next->value = str;
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
