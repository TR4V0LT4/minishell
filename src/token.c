/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlahyani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 22:55:34 by wlahyani          #+#    #+#             */
/*   Updated: 2023/02/02 23:03:03 by wlahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

t_token	*init_token(char *value, int type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	return (token);
}

t_token *get_token(t_lexer *lexer)
{
    t_token	*token; 
    char	*s;
    bool in_double  = 0;
	bool in_single = 0;

    s = NULL;
    skip_spaces(lexer);
    while ((lexer->c != '\0')  && (!istoken(lexer->c) || in_double || in_single))
    {
        if (!in_single && lexer->c == '\"')
            in_double = !in_double;
		if (!in_double && lexer->c == '\'')
            in_single = ! in_single; 

        s = append_to_str(s,lexer->c);
        lexer_next(lexer);
    }
    if (s)
      token =  init_token (s,TOKEN_STRING);
    else
		token = _switch(lexer);
		//free(s);
    return (token);
}

int	istoken(char c)
{
    if (c == '>' || c == '<' ||  c == '|' || c == '\0' || c == ' ')
        return (1);
    return (0);
}

t_token	*_switch(t_lexer *lexer)
{
	if (lexer->c == '>')
	{
		lexer_next(lexer);
		if (lexer->c == '>')
		{
			lexer_next (lexer);
			return (init_token(">>", TOKEN_APPEND));
		}
		return (init_token(">", TOKEN_REDIRECT));
	}   
    if (lexer->c == '<')
	{
		lexer_next(lexer);
		if (lexer->c == '<')
		{
			lexer_next(lexer);
			return (init_token("<<", TOKEN_HEREDOC));
        }
		return (init_token("<", TOKEN_LREDIRECT));
	}
	if (lexer->c == '|')
	{
		lexer_next(lexer);
		return (init_token("|", TOKEN_PIPE));
	}
	else
		return (init_token("EOF", TOKEN_EOF));
}
