
#include "../include/minishell.h"

void	execute(t_list *cmds , char **env)
{
	int	fd[2];
	int	pid;
	int i ;
	t_parser *tmp;
	
	tmp =(t_parser *) malloc(sizeof(t_parser));
	i = 0;
	if((pipe(fd) == -1))
		return ;
	while (cmds)
	{
		tmp = (t_parser *) cmds->content;
		
		pid = fork();
		if (pid == 0)
		{
			if(cmds->next)
			{
				//close(fd[0]);
				//	
				//printf("duping %s\n", tmp->cmd[0]);
				dup2(fd[1], 1);
				close(fd[0]);
				close(fd[1]);
			
				//dup(STDOUT_FILENO);
				//dup2(fd[1],fd[0]);
				//dup2(fd[0],STDIN_FILENO);
				close(0);
				//close(STDOUT_FILENO);
			}
			else
				dup2(fd[0], 0);
			if(tmp->in_file != 0)
			{
				printf("im here\n");
				close(0);
				dup2(tmp->in_file, STDIN_FILENO);
				close(tmp->in_file);
			}
			if(tmp->out_file != 1)
			{
				printf("im here\n");
				close (1);
				dup2(tmp->out_file, STDOUT_FILENO);
				close(tmp->out_file);
			}
			tmp->cmd[0] = add_path(tmp->cmd[0]);
			if (execve(tmp->cmd[0], tmp->cmd, env) == -1)
				exit(1);
		}
		cmds = cmds->next;	
		i++;
	}
	close(fd[0]);
	close(fd[1]);
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
