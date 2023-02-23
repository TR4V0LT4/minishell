/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlahyani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:24:53 by wlahyani          #+#    #+#             */
/*   Updated: 2023/02/23 20:25:14 by wlahyani         ###   ########.fr       */
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

int	check_cmd(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str && str[i])
	{
		if (ft_isprint(str[i]))
			flag = 1;
		i++;
	}
	return (flag);
}

void	dup_std_io(t_list *cmds, t_parser *tmp, int *pipe1, int *buffer)
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
}
