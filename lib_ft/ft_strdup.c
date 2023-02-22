/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhaliff <skhaliff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 09:42:54 by wlahyani          #+#    #+#             */
/*   Updated: 2023/02/23 00:47:25 by skhaliff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*t;

	if (!s1)
		return (NULL);
	t = s_malloc(ft_strlen(s1) + 1);
	if (!t)
		return (0);
	ft_memcpy(t, s1, ft_strlen(s1) + 1);
	return (t);
}
