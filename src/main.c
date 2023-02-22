/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlahyani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:34:49 by wlahyani          #+#    #+#             */
/*   Updated: 2023/02/21 19:35:37 by wlahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

char	*get_new_env(char *s)
{
	t_env	*a;
	t_list	*l;
	int		i;

	i = ft_strlen(s);
	l = g_data.env;
	while (l)
	{
		a = (t_env *) l->content;
		if (ft_strncmp(s, a->key, i) == 0)
			return (a->value);
		l = l->next;
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	g_data.exit_status = 0;
	char	*str;
	t_list	*tokens;
	t_list	*cmd;


	g_data.env = get_env(env);
	cmd = NULL;
	(void)ac;
	(void)av;
	g_data.index = 0;
	while (1)
	{
		signal(SIGINT, handler);
		signal(SIGQUIT, SIG_IGN);
		str = readline("➜ minishell ");
		if (str == NULL)
			exit(0);
		if (!(str[0] != '\0'))
			continue ;
		add_history(str);
		tokens = lexer(str);
		if (check_syntax(tokens))
		{
			deallocate(tokens);
			continue ;
		}
		cmd = fill_command(tokens);
		if(start(cmd))
			continue;
		deallocate(tokens);
	
		free(str);
	}
	return (0);
}
