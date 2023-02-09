/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlahyani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 18:30:45 by wlahyani          #+#    #+#             */
/*   Updated: 2021/12/07 05:11:47 by wlahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*n_dst;
	unsigned char	*n_src;

	n_dst = (unsigned char *)dst;
	n_src = (unsigned char *)src;
	i = 0;
	if (src != dst)
	{
		while (i < n)
		{
			n_dst[i] = n_src[i];
			i++;
		}
	}
	return (dst);
}
