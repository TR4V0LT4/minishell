/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlahyani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 10:32:14 by wlahyani          #+#    #+#             */
/*   Updated: 2021/12/07 03:51:16 by wlahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

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

int	ft_atoi(const char *str)
{
	int					sign;
	unsigned long long	result;
	int					i;

	i = 0;
	while (str[i] && (str[i] == '\f' || str[i] == '\t' || str[i] == ' '
			|| str[i] == '\n' || str[i] == '\r' || str[i] == '\v'))
		i++;
	sign = ft_sign(&str[i], &i);
	result = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		if (result > 9223372036854775807)
		{
			if (sign == 1)
				return (-1);
			return (0);
		}
		i++;
	}
	return (result * sign);
}
