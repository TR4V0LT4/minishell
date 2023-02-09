
#include "../include/minishell.h"

void	execute(t_list *cmds , char **env)
{
	int	fd[2];
	int	pid;
	int i;
	t_parser *tmp;
	
	tmp =(t_parser *) malloc(sizeof(t_parser));
	i = 0;
	while (cmds)
	{
		tmp = (t_parser *) cmds->content;
		pid = fork();
		if (pid == 0)
		{
			tmp->cmd[0] = add_path(tmp->cmd[0]);
			if (execve(tmp->cmd[0], tmp->cmd, env) == -1)
				exit(1);
		}
		close(fd[0]);
		cmds = cmds->next;
		i++;
	}
	while(i--)
		wait(NULL);
}

int start(t_list *list, t_list *envi)
{
	char **tab_env; 
 	if(!builtins(list, envi))
			return 0;
	else if (ft_lstsize(list) > 0)
	{
		tab_env = env_to_tab(envi);
		execute(list,tab_env);
	}
	else
		return(1);
	return(0);
}
