
#include "../include/minishell.h"
void handler_heredoc (int sig)
{
	(void)sig;
	exit(0);
}
void	execute(t_list *cmds , char **env)
{
	(void) env;
	int	pipe1[2] = {-1, -1};
	int buffer[2] = { -1 , -1};
	int	pid;
	int i ;
	t_parser *tmp;
	//int result;

	tmp = (t_parser *) s_malloc(sizeof(t_parser));
	i = 0;
	while (cmds)
	{
		tmp = (t_parser *) cmds->content;
		if(cmds->next)
		{
			if((pipe(pipe1) == -1))
			return ;
		}
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		pid = fork();
		if (pid == 0)
		{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
			if(cmds->next)
			{
				close(pipe1[0]);
				dup2(pipe1[1], 1);
				close(pipe1[1]);
			}
			if(buffer[0] != -1)
			{
				close(buffer[1]);
				dup2(buffer[0], 0);
				close(buffer[0]);
			}
			if(tmp->in_file != 0)
			{
				dup2(tmp->in_file, STDIN_FILENO);
				close(tmp->in_file);
			}
			if(tmp->out_file != 1)
			{
				dup2(tmp->out_file, STDOUT_FILENO);
				close(tmp->out_file);
			}
			if(check_builtin(cmds))
			{
				builtins(cmds);
				exit (0);
			}
			tmp->cmd[0] = add_path(tmp->cmd[0]);
			if (execve(tmp->cmd[0], tmp->cmd, env) == -1)
			{
				printf("minishell : command not found\n");
				exit(0);
			}
		}
		unlink("/tmp/minishell");
		if (tmp->in_file != 0)
			close(tmp->in_file);
		else if (tmp->out_file != 1)
			close(tmp->out_file);
		if (buffer[0] != -1)
			close(buffer[0]);
		if (buffer[1] != -1)
			close(buffer[1]);
		buffer[0] = pipe1[0];
		buffer[1] = pipe1[1];
		pipe1[0] = -1;
		pipe1[1] = -1;
		cmds = cmds->next;
		i++;
	}
	while (waitpid(-1, NULL, 0) != -1 );
		//wait(NULL);
		
	// if(cmds->next == NULL)
	// 	waitpid(pid, &result, 0);
	// int exit_status = WIFEXITED(result); // exit status
}

int start(t_list *list)
{
	char **tab_env;

	if (ft_lstsize(list) == 1 && check_builtin(list))
		builtins(list);
	else
	{
		tab_env = env_to_tab(g_data.env);
		execute(list,tab_env);
	}
	return(0);
}
