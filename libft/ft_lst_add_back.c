/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_add_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aryamamo <aryamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:35:23 by aryamamo          #+#    #+#             */
/*   Updated: 2024/12/12 15:35:26 by aryamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lst_last;

	if (!lst || !new)
		return ;
	if (*lst)
	{
		lst_last = ft_lstlast(*lst);
		lst_last->next = new;
	}
	else
		*lst = new;
}
