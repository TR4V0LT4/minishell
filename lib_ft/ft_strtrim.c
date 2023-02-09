/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlahyani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:56:13 by wlahyani          #+#    #+#             */
/*   Updated: 2021/12/07 05:05:21 by wlahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	find_edges(const char *s1, char const *set, int len, int step)
{
	int	i;
	int	j;
	int	found;

	if (!s1)
		return (0);
	i = len;
	while (i >= 0 && s1[i])
	{
		j = 0;
		found = 0;
		while (set[j])
		{
			if (set[j] == s1[i])
			{
				found = 1;
				i += step;
				break ;
			}
			j++;
		}
		if (!found)
			return (i);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*t;
	int		len;
	int		start;
	int		end;
	int		i;

	i = 0;
	if (!s1)
		return (NULL);
	start = find_edges(s1, set, 0, 1);
	end = find_edges(s1, set, ft_strlen(s1) - 1, -1);
	len = end - start + 1;
	t = (char *) malloc(sizeof(char) * len +1);
	if (!t)
		return (0);
	while (i < len)
	{
		if (end == 0 && start == 0)
			break ;
		t[i] = s1[start];
		i++;
		start++;
	}
	t[i] = '\0';
	return (t);
}
