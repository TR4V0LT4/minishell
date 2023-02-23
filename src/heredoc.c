/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhaliff <skhaliff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 22:06:27 by wlahyani          #+#    #+#             */
/*   Updated: 2023/02/23 17:51:54 by wlahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	heredoc_signals(int sig)
{
	(void)sig;
	exit(0);
}

void	print_exit_status(int *i)
{
	printf("%d\n", g_data.exit_status);
	g_data.exit_status = 0;
	(*i)++;
}

char	*expanding(char *str)
{
	int		i;
	char	*string;
	char	*var_name;

	i = 0;
	string = NULL;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (str[i] == '?')
				print_exit_status(&i);
			var_name = get_var_name(str + i);
			string = expand(string, var_name);
			i += ft_strlen(var_name);
			free(var_name);
		}
		else
			string = append_to_str(string, str[i]);
		i++;
	}
	return (string);
}

void	child_process(int fd, int flag, char *delimiter)
{
	char	*str;

	str = NULL;
	signal(SIGINT, heredoc_signals);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		str = readline(">");
		if (ft_strcmp(str, delimiter))
		{
			if (!flag)
				str = expanding(str);
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

int	heredoc(char *delimiter, int flag)
{
	char		*path;
	int			fd;
	int			pid;

	path = ft_strjoin("/tmp/", "minishell");
	fd = open(path, O_CREAT | O_WRONLY, 0600);
	pid = fork();
	if (pid == 0)
		child_process(fd, flag, delimiter);
	else
		wait(NULL);
	close(fd);
	fd = open(path, O_RDONLY);
	return (fd);
}
