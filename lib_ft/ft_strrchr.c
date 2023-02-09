/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlahyani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 10:00:24 by wlahyani          #+#    #+#             */
/*   Updated: 2021/12/07 05:04:58 by wlahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;
	int	j;
	int	f;

	f = 0;
	j = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == (char) c)
		{
			j = i;
			f = 1;
		}
		i++;
	}	
	if (f)
		return ((char *)&str[j]);
	if (c == '\0')
		return ((char *)&str[i]);
	return (0);
}
