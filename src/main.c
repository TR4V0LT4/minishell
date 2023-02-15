#include "../include/minishell.h"


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
	while (1)
	{
		str = readline("➜ minishell ");
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
		print_tokens(tokens);
		print_cmd(cmd);
		start(cmd, t_env);
		deallocate(tokens);
	}
	return (0);
}
