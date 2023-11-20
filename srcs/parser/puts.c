/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 04:17:06 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/21 05:54:27 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_command_list(t_list *list)
{
	if (list == NULL)
		return ;
	printf("%s\n", list->content);
	print_command_list(list->next);
}

void	print_redir_list(t_list *list)
{
	t_redir	*redir;

	if (list == NULL || list->content == NULL)
	{
		puts("given redirection list reaches the end.");
		return ;
	}
	redir = (t_redir *)list->content;
	printf("%d\n", redir->type);
	if (redir->filename == NULL)
		return ;
	printf("%s\n", redir->filename);
	print_redir_list(list->next);
}

void	print_node(t_ast_node *node)
{
	puts("Enter new node.");
	if (node == NULL)
	{
		puts("Given node is NULL.");
		return ;
	}
	printf("%d\n", node->type);
	if (node->command != NULL)
	{
		puts("Start printing command list.");
		print_command_list(node->command);
	}
	if (node->redir != NULL)
	{
		puts("Start printing redirection list.");
		print_redir_list(node->redir);
	}
	print_node(node->left);
	print_node(node->right);
}
