/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlahyani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 22:16:54 by wlahyani          #+#    #+#             */
/*   Updated: 2023/02/21 22:18:16 by wlahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	handler()
{
	write (1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_free(char	**t)
{
	int	i;

	i = -1;
	while (t[++i])
		free (t[i]);
}

char	*get_var_name(char *str)
{
	int i;
	char *name;

	i = 0;
	name = NULL;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_' ) )
	{
		name = append_to_str(name, str[i]);
		if (i == 1 && str[i] == '?')
			break;
		i++;
	}
	if (!name)
		name = append_to_str(name, '\0');
	return (name);
}

char	*expand(char *result, char *var_name)
{
	char *value;
	char *tmp;

	if (!ft_strcmp(var_name, "?"))
		value = ft_itoa(g_data.exit_status);
	else
		value  = get_new_env(var_name);
	tmp = result;
	result = ft_strjoin(result, value);
	if (result == NULL)
		result = append_to_str(result, '\0');
	free(tmp);
	return (result);
}

char	**realloc_cmd(char **cmd, char *str)
{
	char	**tmp;
	int		i;

	i = 0;
	if (!cmd[0])
	{
		if(!ft_strdup(str))
			cmd[0] = "\0";
		else
			cmd[0] = ft_strdup(str);
	}
	else
	{
		while (cmd[i])
			i++;
		tmp = (char **)s_malloc(sizeof(char *) * (i + 1));
		i = 0;
		while (cmd[i])
		{	
			tmp[i] = ft_strdup(cmd[i]);
			i++;
		}
		tmp[i] = NULL;
		cmd = (char **) s_malloc(sizeof(char *) * (i + 2));
		i = 0;
		while (tmp[i])
		{	
			cmd[i] = tmp[i];
			i++;
		}
		cmd[i] = ft_strdup(str);
		cmd [i + 1] = NULL;
	}
	return (cmd);
}
void debug_print_token(t_token *token)
{
    if(!token)
        printf("null\n");
    else
        printf("value = %s &&  type = %d\n",token->value, token->type );
}
void deallocate(t_list *list)
{
     t_list *curr = list;
     t_list *tmp;
    
    while(curr)
    {
        free(curr->content);
        tmp = curr;
        curr = curr->next;
        free(tmp);
    }
}
void print_tokens(t_list *list)
{
    t_list * curr = list;
    while(curr)
    {
        debug_print_token((t_token *) curr->content);
        curr = curr->next;
    }
}
void print_cmd(t_list *list)
{
    int i = 0;
    t_parser *curr = (t_parser *)s_malloc(sizeof(t_parser ));
        while(list)
        {
               curr = (t_parser *)list->content;
                i = 0;
                while(curr->cmd[i])
                {
                    printf("cmd [%d] = %s\n",i,curr->cmd[i]);
                    i++;
                }
             printf("in_file =  %d && out_file = %d\n", curr->in_file,curr->out_file);
			 printf("============================================================================\n");
            list = list->next;
        }
}
