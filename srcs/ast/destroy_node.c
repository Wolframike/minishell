/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:54:16 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/22 15:54:19 by misargsy         ###   ########.fr       */
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
