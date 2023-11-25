/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 22:11:54 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/23 12:23:34 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*cur;
	t_list	*next;

	if (lst == NULL)
		return ;
	cur = *lst;
	while (cur)
	{
		next = cur->next;
		if (del != NULL)
			del(cur->content);
		free(cur);
		cur = next;
	}
	*lst = NULL;
}
