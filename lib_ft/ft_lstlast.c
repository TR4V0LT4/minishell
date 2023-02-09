/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlahyani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 15:54:29 by wlahyani          #+#    #+#             */
/*   Updated: 2022/06/11 15:55:47 by wlahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{	
	t_list	*curr;

	if (!lst)
		return (lst);
	curr = lst;
	while (curr->next)
		curr = curr->next;
	return (curr);
}
