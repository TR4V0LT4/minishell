#include "../include/minishell.h"

t_list *get_env(char **env)
{
	int	i;
	char **all;
	t_env * temp_var;
	t_list  *env_list;
	
	i = 0;
	env_list  =  NULL;
	while (env[i] != NULL)
	{
		temp_var = malloc(sizeof(t_env));
		all = ft_split(env[i], '=');
		temp_var->key = all[0];
		temp_var->value= all[1];
		ft_lstadd_back(&env_list, ft_lstnew(temp_var));
		free(all);
		i++;
	}
	return (env_list);
}

char **env_to_tab(t_list *list)
{
	int size;
	char **t;
	char *tmp;
	t_env *curr;
	int i;

	i = 0;
	size = ft_lstsize(list);
	t = (char **)malloc(sizeof(char *) * (size + 1));
	t[size] = NULL;
	while(list)
	{
		curr = (t_env *)list->content;
		tmp = ft_strjoin(curr->key, "=");
		t[i] = ft_strjoin(tmp,curr->value);
		i++;
		list = list->next;
		free(tmp);
	}
	return (t);
}
size_t get_env_size(char **env)
{
	int size = 0;
	while(env[size])
		size++;
	return size;
}
char *add_path(char *cmd)
{
    char **path;
    char *command;
    int i = 0;
    path = ft_split(getenv("PATH"), ':');
    while(path[i])
    {
        command = ft_strjoin(path[i],"/");
        command = ft_strjoin(command,cmd);  
		if(!access( command , R_OK ))
		{
			return (command);
		}
		i++;
        free(command);
    }
	return(cmd);
}