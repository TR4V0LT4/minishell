/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhaliff <skhaliff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:23:41 by wlahyani          #+#    #+#             */
/*   Updated: 2023/02/23 00:45:56 by skhaliff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handler_heredoc(int sig)
{
	(void)sig;
	exit(0);
}

void	rederacting(int input, int output)
{
	if (input != 0)
	{
		dup2(input, STDIN_FILENO);
		close(input);
	}
	if (output != 1)
	{
		dup2(output, STDOUT_FILENO);
		close(output);
	}
}

void	execute(t_list *cmds, char **env)
{
	int			pipe1[2] = {-1 , -1};
	int			buffer[2] = {-1, -1};
	int			pid;
	int			i;
	t_parser	*tmp;

	tmp = (t_parser *) s_malloc(sizeof(t_parser));
	i = 0;
	while (cmds)
	{
		tmp = (t_parser *)cmds->content;
		if (cmds->next)
		{
			if ((pipe(pipe1) == -1))
				return ;
		}
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_IGN);
			if (cmds->next)
			{
				close(pipe1[0]);
				dup2(pipe1[1], 1);
				close(pipe1[1]);
			}
			if (buffer[0] != -1)
			{
				close(buffer[1]);
				dup2(buffer[0], 0);
				close(buffer[0]);
			}
			rederacting(tmp->in_file, tmp->out_file);
			if (check_builtin(cmds))
			{
				builtins(cmds);
				exit (0);
			}
			tmp->cmd[0] = add_path(tmp->cmd[0]);
			if (execve(tmp->cmd[0], tmp->cmd, env) == -1)
			{
				write(2, "minishell : command not found\n", 30);
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
	while (waitpid(-1, NULL, 0) != -1)
		;
	//wait(NULL);
	// if(cmds->next == NULL)
	// 	waitpid(pid, &result, 0);
	// int exit_status = WIFEXITED(result); // exit status
}

int	start(t_list *list)
{
	char		**tab_env;
	t_parser	*cmd;

	cmd = (t_parser *) s_malloc(sizeof(t_parser));
	cmd = (t_parser *)list->content;
	if (ft_lstsize(list) == 1 && check_builtin(list))
	{
		builtins(list);
	}
	else
	{
		tab_env = env_to_tab(g_data.env);
		execute(list, tab_env);
	}
	return (0);
}
