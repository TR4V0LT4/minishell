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
	t_list	*t_env;

	t_env = get_env(env);
	cmd = NULL;
	(void)ac;
	(void)av;
	
    signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		str = readline("➜ minishell ");
		if(str == NULL)
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
		//print_cmd(cmd);
		start(cmd, t_env);
		deallocate(tokens);

		free(str);
	}
	return (0);
}
