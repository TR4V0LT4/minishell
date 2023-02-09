/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlahyani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 21:51:55 by wlahyani          #+#    #+#             */
/*   Updated: 2021/12/07 03:52:37 by wlahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static	int	ft_power(int nb, int power)
{
	int	n;

	n = 1;
	if (power == 0)
		return (1);
	while (power > 0)
	{
		n = n * nb;
		power--;
	}
	if (power < 0)
		return (0);
	return (n);
}

static	int	ft_len(int n)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n > 9)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*t;
	int		len;
	int		i;

	i = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	len = ft_len(n);
	t = (char *)malloc(sizeof(char) * (len + 1));
	if (!t)
		return (NULL);
	if (n < 0)
	{
		t[0] = '-';
		n *= -1;
		i++;
		len--;
	}
	if (n >= 0)
		while (len)
			t[i++] = ((n / ft_power (10, (len-- - 1)) % 10) + '0');
	t[i] = '\0';
	return (t);
}
