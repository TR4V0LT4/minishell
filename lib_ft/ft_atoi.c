/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhaliff <skhaliff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 10:32:14 by wlahyani          #+#    #+#             */
/*   Updated: 2023/02/23 00:48:15 by skhaliff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_sign(const char *str, int *i)
{	
	int	sign;

	sign = 1;
	if (str[0] == '-' || str[0] == '+')
	{
		if (str[0] == '-')
			sign = -1;
		*i = *i + 1;
	}
	return (sign);
}

int	ft_atoi(const char *str, long long *b)
{
	int					sign;
	unsigned long long	result;
	int					i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && (str[i] == '\f' || str[i] == '\t' || str[i] == ' '
			|| str[i] == '\n' || str[i] == '\r' || str[i] == '\v'))
		i++;
	sign = ft_sign(&str[i], &i);
	result = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		if (sign > 0 && (__LONG_LONG_MAX__) < result)
			return (0);
		else if (sign < 0 && (unsigned long long)__LONG_LONG_MAX__ + 1 < result)
			return (0);
		i++;
	}
	(*b) = result * sign;
	return (1);
}
