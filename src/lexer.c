/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlahyani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 22:02:36 by wlahyani          #+#    #+#             */
/*   Updated: 2023/02/21 19:36:16 by wlahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	init_lexer(t_lexer *lexer, char *src)
{
	lexer->src = src;
	lexer->index = 0;
	lexer->c = lexer->src[lexer->index];
}

void	lexer_next(t_lexer *lexer)
{
	lexer->index++;
	lexer->c = lexer->src[lexer->index];
}

t_list	*lexer(char *src)
{
	t_lexer	lexer;
	t_token	*token;
	t_list	*list ;

	init_lexer(&lexer, src);
	list = NULL;
	while (lexer.c != '\0')
	{
		token = get_token(&lexer);
		ft_lstadd_back(&list, ft_lstnew(token));
	}
	token = init_token (NULL, TOKEN_EOF);
	ft_lstadd_back(&list, ft_lstnew(token));
	return (list);
}

void	skip_spaces(t_lexer *lexer)
{
	if (!lexer->src)
		return ;
	while (lexer->c && lexer->c == ' ')
		lexer_next(lexer);
}

char	*append_to_str(char *str, char c)
{
	char	*tmp;
	char	*str_char;

	tmp = str;
	str_char = s_malloc(sizeof(char) * 2);
	str_char[0] = c;
	str_char[1] = '\0';
	if (!str)
	{
		str = str_char;
		return (str);
	}
	else
	{
		str = ft_strjoin(str, str_char);
		free(tmp);
		free(str_char);
	}
	return (str);
}
