/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlahyani <wlahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:23:41 by wlahyani          #+#    #+#             */
/*   Updated: 2023/02/23 21:17:18 by wlahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execution_child(t_list *cmds, t_parser *tmp, int *pipe1, int *buffer)
{
	dup_std_io(cmds, tmp, pipe1, buffer);
	if (check_builtin(cmds))
	{
		builtins(cmds);
		exit (0);
	}
	tmp->cmd[0] = add_path(tmp->cmd[0]);
	if (check_cmd(tmp->cmd[0]))
	{
		if (execve(tmp->cmd[0], tmp->cmd, tmp->env) == -1)
		{
			write(2, "minishell : command not found\n", 30);
			exit(0);
		}
	}
	else
		exit(1);
}

void	closing_fds(t_parser *tmp, int *pipe1, int *buffer)
{
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
}

void	execution_loop(t_list *cmds, t_parser *tmp, int *pipe1, int *buffer)
{
	int	pid;

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
			execution_child(cmds, tmp, pipe1, buffer);
		closing_fds(tmp, pipe1, buffer);
		cmds = cmds->next;
	}
}

void	execute(t_list *cmds)
{
	int			pipe1[2];
	int			buffer[2];
	t_parser	*tmp;

	pipe1[0] = -1;
	pipe1[1] = -1;
	buffer[0] = -1;
	buffer[1] = -1;
	tmp = (t_parser *) s_malloc(sizeof(t_parser));
	execution_loop(cmds, tmp, pipe1, buffer);
	wait(NULL);
	while (waitpid(-1, NULL, 0) != -1)
		;
}

void	start(t_list *list)
{
	t_parser	*cmd;

	cmd = (t_parser *) s_malloc(sizeof(t_parser));
	cmd = (t_parser *)list->content;
	if (ft_lstsize(list) == 1 && check_builtin(list))
		builtins(list);
	else
	{
		cmd->env = env_to_tab(g_data.env);
		execute(list);
	}
}

// while (cmds)
// {
// 	tmp = (t_parser *)cmds->content;
// 	if (cmds->next)
// 	{
// 		if ((pipe(pipe1) == -1))
// 			return ;
// 	}
// 	signal(SIGINT, SIG_IGN);
// 	signal(SIGQUIT, SIG_IGN);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		signal(SIGINT, SIG_DFL);
// 		signal(SIGQUIT, SIG_IGN);
// 		if (cmds->next)
// 		{
// 			close(pipe1[0]);
// 			dup2(pipe1[1], 1);
// 			close(pipe1[1]);
// 		}
// 		if (buffer[0] != -1)
// 		{
// 			close(buffer[1]);
// 			dup2(buffer[0], 0);
// 			close(buffer[0]);
// 		}
// 		rederacting(tmp->in_file, tmp->out_file);
// 		if (check_builtin(cmds))
// 		{
// 			builtins(cmds);
// 			exit (0);
// 		}
// 		tmp->cmd[0] = add_path(tmp->cmd[0]);
// 		if (check_cmd(tmp->cmd[0]))
// 		{
// 			if (execve(tmp->cmd[0], tmp->cmd, env) == -1)
// 			{
// 				write(2, "minishell : command not found\n", 30);
// 				exit(0);
// 			}
// 		}
// 		else
// 			exit(1);
// 	}
// 	unlink("/tmp/minishell");
// 	if (tmp->in_file != 0)
// 		close(tmp->in_file);
// 	else if (tmp->out_file != 1)
// 		close(tmp->out_file);
// 	if (buffer[0] != -1)
// 		close(buffer[0]);
// 	if (buffer[1] != -1)
// 		close(buffer[1]);
// 	buffer[0] = pipe1[0];
// 	buffer[1] = pipe1[1];
// 	pipe1[0] = -1;
// 	pipe1[1] = -1;
// 	cmds = cmds->next;
// 	i++;
// }
