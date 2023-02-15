
#include "../include/minishell.h"

		//if()

			// if( i != 0)
			// {
			// 	close(pipe1[1]);
			// 	dup2(pipe1[0], 0);
			// 	close(pipe1[0]);

				//dup2(pipe2[1], 1);
				//close(pipe2[1]);

				
				// dup2(pipe2[0], pipe1[0]);
				// close(pipe2[0]);
				
				// close(pipe1[0]);
				
				// dup2(pipe2[1], 1);
				// close(pipe2[1]);
				// close(pipe1[0]);
				// close(pipe1[1]);
				// close (1);
		
			// else
			// {
			// 	close(pipe1[1]);
			// 	dup2(pipe1[0], 0);
			// 	close(pipe1[0]);
			// }	
			// if(tmp->in_file != 0)
			// {
			// 	close(0);
			// 	dup2(tmp->in_file, STDIN_FILENO);
			// 	close(tmp->in_file);
			// }
			// if(tmp->out_file != 1)
			// {
			// 	close (1);
			// 	dup2(tmp->out_file, STDOUT_FILENO);
			// 	close(tmp->out_file);
			// }

	
void	execute(t_list *cmds , char **env)
{
	int	pipe1[2] = {-1, -1};
	int buffer[2] = { -1 , -1};
	int	pid;
	int i ;
	t_parser *tmp;
	
	tmp =(t_parser *) malloc(sizeof(t_parser));
	i = 0;

	while (cmds)
	{
		tmp = (t_parser *) cmds->content;
		if(cmds->next)
		{
			if((pipe(pipe1) == -1))
			return ;
		}
		pid = fork();
		if (pid == 0)
		{
			if(cmds->next)
			{
				close(pipe1[0]);
				dup2(pipe1[1], 1);
				close(pipe1[1]);
			}
			if(buffer[0] != -1)
			{
				close(buffer[1]);
				dup2(buffer[0],0);
				close(buffer[0]);
			}
			tmp->cmd[0] = add_path(tmp->cmd[0]);
			if (execve(tmp->cmd[0], tmp->cmd, env) == -1)
				exit(1);
		
		}
		if (buffer[0] != -1)
			close(buffer[0]);
		if (buffer[1] != -1)
			close(buffer[1]);
		buffer[0] = pipe1[0];
		buffer[1] = pipe1[1];
		pipe1[0] = -1;
		pipe1[1] = -1;
		wait(NULL);
		cmds = cmds->next;	
		i++;
	}


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
