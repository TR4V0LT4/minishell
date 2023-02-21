/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhaliff <skhaliff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 22:10:00 by wlahyani          #+#    #+#             */
/*   Updated: 2023/02/20 16:45:33 by skhaliff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void 	*s_malloc(int size)
{
	void	*s;
	s = malloc(size);
	g_data.to_free[g_data.index] = s;
	g_data.index++;
	return (s);
}

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
void heredoc_signals()
{
	exit(0);
}
char    *expanding(char *str)
{
	int             i;
    char *string;
    char *var_name;
	
	i = 0;
    string = NULL;
    while (str[i])
    {
        if (str[i] == '$')
        {
			i++;
            	if (str[i ] == '?')
				{
            	    printf("%d\n", g_data.exit_status);
					i++;
				}
			var_name = get_var_name(str + i);
            string = expand(string, var_name);
            i += ft_strlen(var_name);
            free(var_name);
        }
		else
			string = append_to_str(string, str[i]);
        i++;
    }
    return (string);
}
int	heredoc(char *value, int flag)
{
	char		*str = NULL;
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

		while (1)
		{
			str = readline(">");
			if(!flag)
				str = expanding(str);
			if (ft_strcmp(str, value) )
			{
				write(fd, str, ft_strlen(str));
				write(fd, "\n", 1);
			}
			else
				break;
		
		}
		write(fd, "\0", 1);	
		close(fd);
		exit(0);
	}
	else
		wait(NULL);
	close(fd);
	fd = open(path, O_RDONLY);
	return fd;
}
char    *remove_quotes(char *str , int *heredoc_flag, int prev_type)
{
	int		i;
	char	*string;
	char	*var_name;
	
	i = 0;
    string = NULL;
    while (str[i])
    {
	    if (str[i] == '\"')
        {
            i++;
            while (str[i] && str[i] != '\"')
            {
        		if (str[i] == '$')
    			{
					if(str[i+1] == '?')
						var_name = ft_strdup("?");
					else
               			var_name = get_var_name(str+i);
  					string = expand(string, var_name);
                    i += ft_strlen(var_name);
                	free(var_name);
				}
        		else
                	string = append_to_str(string, str[i]);
				i++;
 			}
		i++;
		if (prev_type == TOKEN_HEREDOC)
			*heredoc_flag = 1;
     	}
     	else if (str[i] == '\'')
        {
            i++;
            while (str[i] && str[i] != '\'')
            {
                string = append_to_str(string, str[i]);
                i++;
            }
            i++;
			if (prev_type == TOKEN_HEREDOC)
				*heredoc_flag = 1;
        }
        else
        {
            if (str[i] == '$')
            {
                var_name = get_var_name(str + i);
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
t_list *parsing_quotes(t_list *tokens, int *flag)
{
	t_list *tmp;
	t_token *curr;
	int t = 0;

	tmp = tokens;
	curr = (t_token *)tokens->content;
	while(tmp && curr->type != TOKEN_EOF )
	{
		if(curr->type == TOKEN_STRING)
			curr->value = remove_quotes(curr->value ,flag, t);
		t = curr->type;	
		tmp = tmp->next;
		curr = (t_token *)tmp->content;
	}
	return (tokens);
} 
t_list	*fill_command(t_list *tokens)
{
	t_list		*cmd_list;
	t_token		*curr;
	t_parser	*tmp;
	int flag = 0;


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
				tmp->out_file = open(curr->value, O_CREAT | O_RDWR | O_APPEND, 0664);
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
					printf("minishell: %s: No such file or directory\n", curr->value);
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
		if(tokens->next)
		{
			tokens = tokens->next;
			curr = (t_token *) tokens->content;
		}
	}
	ft_lstadd_back(&cmd_list, ft_lstnew(tmp));
	return (cmd_list);
}

int	quotes_checker(char *str)
{
	int		i;
	char *string;
	i = 0;
	string = NULL;

	while (str[i])
	{
		if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
			if (str[i] == '\0')
				return (1);
			i++;
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (str[i] == '\0')
				return (1);
			i++;
		}
		else
			i++;
	}
	return 0;
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
		if (curr->type == TOKEN_PIPE && (next->type == TOKEN_REDIRECT  || next->type == TOKEN_LREDIRECT))
		{
			curr = (t_token *) tokens->content;
			next = (t_token *) tokens->next->content;
		}
		else if(curr->type == TOKEN_STRING)
		{
			 if(quotes_checker(curr->value))
				return (printf("minishell: syntax error unexpected token `\\n'\n"));
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
