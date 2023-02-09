/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlahyani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 10:28:55 by wlahyani          #+#    #+#             */
/*   Updated: 2021/12/07 05:03:43 by wlahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	if (s2[0] == '\0')
		return ((char *)s1);
	i = 0;
	while (s1[i] && i < n)
	{
		j = 0;
		if (s1[i] == s2[j])
		{
			while (i + j < n && s1[i + j] == s2[j])
			{
				j++;
				if (!s2[j])
					return ((char *)&s1[i]);
			}
		}
		i++;
	}
	return (0);
}
