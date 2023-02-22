#include "../include/minishell.h"

char	*remove_quotes(char *str, int *heredoc_flag, int prev_type)
{
	int		i;
	char	*string;
	char	*var_name;

	i = 0;
	string = NULL;
	while (str[i])
	{
		if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
			{
				if (str[i] == '$' && prev_type != TOKEN_HEREDOC)
				{
					if (str[i + 1] == '?')
						var_name = ft_strdup("?");
					else
						var_name = get_var_name(str + i + 1);
					string = expand(string, var_name);
					i += ft_strlen(var_name);
					free(var_name);
				}
				else
					string = append_to_str(string, str[i]);
				i++;
			}
		i++;
			if (prev_type == TOKEN_HEREDOC)
			*heredoc_flag = 1;
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
			{
				string = append_to_str(string, str[i]);
				i++;
			}
			i++;
			if (prev_type == TOKEN_HEREDOC)
				*heredoc_flag = 1;
		}
		else
		{
			if (str[i] == '$' && prev_type != TOKEN_HEREDOC)
			{
				if (str[i + 1] == '?')
					var_name = ft_strdup("?");
				else
					var_name = get_var_name(str + i + 1);
					string = expand(string, var_name);
				i += ft_strlen(var_name);
				free(var_name);
			}
			else
				string = append_to_str(string, str[i]);
			i++;
		}
	}
	if (!string)
		return ("\0");
	return (string);
}

int	quotes_checker(char *str)
{
	int		i;
	char	*string;

	i = 0;
	string = NULL;
	while (str[i])
	{
		if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
			if (str[i] == '\0')
				return (1);
			i++;
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (str[i] == '\0')
				return (1);
			i++;
		}
		else
			i++;
	}
	return (0);
}

t_list	*parsing_quotes(t_list *tokens, int *flag)
{
	t_list	*tmp;
	t_token	*curr;
	int		previous;

	previous = 0;
	tmp = tokens;
	curr = (t_token *)tokens->content;
	while (tmp && curr->type != TOKEN_EOF)
	{
		if (curr->type == TOKEN_STRING)
			curr->value = remove_quotes(curr->value, flag, previous);
		previous = curr->type;
		tmp = tmp->next;
		curr = (t_token *)tmp->content;
	}
	return (tokens);
}
