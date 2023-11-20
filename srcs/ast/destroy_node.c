/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_ast_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:33:38 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/21 00:16:12 by knishiok         ###   ########.fr       */
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
	free(node->left);
	free(node->right);
	ft_lstclear(&node->command, free);
	ft_lstclear(&node->redir, (void (*)(void *))destroy_redir);
	free(node);
}
