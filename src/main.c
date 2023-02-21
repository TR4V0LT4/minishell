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
		start(cmd);
		deallocate(tokens);

		free(str);
	}
	return (0);
}
