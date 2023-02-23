/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhaliff <skhaliff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 22:16:54 by wlahyani          #+#    #+#             */
/*   Updated: 2023/02/23 18:40:20 by wlahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_var_name(char *str)
{
	int		i;
	char	*name;

	i = 0;
	name = NULL;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_' ))
	{
		name = append_to_str(name, str[i]);
		if (i == 1 && str[i] == '?')
			break ;
		i++;
	}
	if (!name)
		name = append_to_str(name, '\0');
	return (name);
}

char	*expand(char *result, char *var_name)
{
	char	*value;
	char	*tmp;

	if (!ft_strcmp(var_name, "?"))
		value = ft_itoa(g_data.exit_status);
	else
		value = get_new_env(var_name);
	tmp = result;
	result = ft_strjoin(result, value);
	if (result == NULL)
		result = append_to_str(result, '\0');
	free(tmp);
	return (result);
}

char	*one_cmd(char *str)
{
	if (!ft_strdup(str))
		return ("\0");
	else
		return (ft_strdup(str));
}

char	**realloc_cmd(char **cmd, char *str)
{
	char	**tmp;
	int		i;

	i = 0;
	if (!cmd[0])
		cmd[0] = one_cmd(str);
	else
	{
		while (cmd[i])
			i++;
		tmp = (char **)s_malloc(sizeof(char *) * (i + 1));
		i = -1;
		while (cmd[++i])
			tmp[i] = ft_strdup(cmd[i]);
		tmp[i] = NULL;
		cmd = (char **) s_malloc(sizeof(char *) * (i + 2));
		i = -1;
		while (tmp[++i])
			cmd[i] = tmp[i];
		cmd[i] = ft_strdup(str);
		cmd [i + 1] = NULL;
	}
	return (cmd);
}
