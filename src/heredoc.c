/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlahyani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 22:06:27 by wlahyani          #+#    #+#             */
/*   Updated: 2023/02/21 22:15:03 by wlahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	heredoc_signals(int sig)
{
	(void)sig;
	exit(0);
}

int	heredoc(char *value, int flag)
{
	char		*str;
	char		*path;
	int			pid;
	int			fd;

	str = NULL;
	path = ft_strjoin("/tmp/", "minishell");
	fd = open(path, O_CREAT | O_WRONLY, 0600);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, heredoc_signals);
		signal(SIGQUIT, SIG_IGN);
		while (1)
		{
			str = readline(">");
			if (!flag)
				str = expanding(str);
			if (ft_strcmp(str, value))
			{
				write(fd, str, ft_strlen(str));
				write(fd, "\n", 1);
			}
			else
				break ;
		}
		write(fd, "\0", 1);	
		close(fd);
		exit(0);
	}
	else
		wait(NULL);
	close(fd);
	fd = open(path, O_RDONLY);
	return (fd);
}
