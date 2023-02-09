/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlahyani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 10:19:46 by wlahyani          #+#    #+#             */
/*   Updated: 2021/12/07 03:53:18 by wlahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*w1;
	unsigned char	*w2;

	w1 = (unsigned char *)s1;
	w2 = (unsigned char *)s2;
	i = 0;
	while (n > 0)
	{
		if (w1[i] != w2[i])
			return (w1[i] - w2[i]);
		i++;
		n--;
	}
	return (0);
}
