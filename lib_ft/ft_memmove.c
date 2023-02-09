/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlahyani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 19:29:22 by wlahyani          #+#    #+#             */
/*   Updated: 2021/12/07 03:54:34 by wlahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*n_dst;
	unsigned char	*n_src;

	n_dst = (unsigned char *)dst;
	n_src = (unsigned char *)src;
	if ((n_src < n_dst))
	{
		while (len--)
			n_dst[len] = n_src[len];
		return (dst);
	}
	else
		return (ft_memcpy(dst, src, len));
}
