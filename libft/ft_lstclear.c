/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 22:11:54 by knishiok          #+#    #+#             */
/*   Updated: 2023/09/24 22:27:03 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*cur;
	t_list	*next;

	if (lst == NULL || del == NULL)
		return ;
	cur = *lst;
	while (cur)
	{
		next = cur->next;
		del(cur->content);
		free(cur);
		cur = next;
	}
	*lst = NULL;
}
