/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlahyani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 21:21:16 by wlahyani          #+#    #+#             */
/*   Updated: 2021/12/07 03:57:08 by wlahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static	int	count_words(char const *p, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (p[i])
	{
		while (p[i] && p[i] != c)
		{
			count++;
			i++;
			break ;
		}
		while (p[i] && p[i] != c)
			i++;
		if (p[i] == c && c != '\0')
			i++;
	}
	return (count);
}

static	char	**ft_copy(char **t, char const *s, int wn, char c)
{
	int	j;
	int	i;
	int	k;

	j = 0;
	i = 0;
	while (j < wn && s[i])
	{	
		while (s[i] && s[i] == c)
			i++;
		k = 0;
		while (s[i] && s[i] != c)
		{
			t[j][k] = s[i];
			i++;
			k++;
		}
		t[j][k] = '\0';
		j++;
	}
	return (t);
}

static	void	myfree(char **t, int j)
{
	while (j > 0)
	{
		free (t[j - 1]);
		j--;
	}
	free (t);
	t = NULL;
	return ;
}

static	void	ft_my_alloc(char **t, char const *s, int wn, char c)
{	
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	while (s[i] && j < wn)
	{
		while (s[i] && s[i] == c)
			i++;
		len = 0;
		while (s[i] && s[i] != c)
		{
			len++;
			i++;
		}
		t[j] = (char *)malloc(sizeof(char) * (len + 1));
		if (!t[j])
			return (myfree(t, j));
		j++;
	}
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		wn;
	char	**t;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	wn = count_words(s, c);
	t = (char **)malloc(sizeof(char *) * wn + sizeof(NULL));
	if (!t)
		return (0);
	t[wn] = NULL;
	ft_my_alloc(t, s, wn, c);
	if (!t)
		return (0);
	return (ft_copy(t, s, wn, c));
}
