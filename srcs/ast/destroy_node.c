/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 06:05:03 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/25 15:48:24 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	destroy_redir(t_redir *redir)
{
	if (redir == NULL)
		return ;
	free(redir->filename);
	free(redir);
}

void	destroy_ast_node(t_ast_node *node)
{
	if (node == NULL)
		return ;
	ft_lstclear(&node->command, free);
	ft_lstclear(&node->redir, (void (*)(void *))destroy_redir);
	destroy_ast_node(node->left);
	destroy_ast_node(node->right);
	free(node);
}
