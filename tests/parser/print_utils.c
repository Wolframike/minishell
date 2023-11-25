/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 15:42:55 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/25 15:43:09 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_command_list(t_list *list)
{
	if (list == NULL)
	{
		puts("(null)");
		puts("==========================");
		return ;
	}
	printf("%s->", list->content);
	print_command_list(list->next);
}

void	print_redir_list(t_list *list)
{
	t_redir	*redir;

	if (list == NULL || list->content == NULL)
	{
		puts("(null)");
		puts("==========================");
		return ;
	}
	redir = (t_redir *)list->content;
	printf("Redirection type: %d\n", redir->type);
	if (redir->filename == NULL)
		return ;
	printf("Redirection filename: %s\n", redir->filename);
}

void	print_node(t_ast_node *node)
{
	if (node == NULL)
	{
		printf("(null)\n");
		puts("==========================");
		return ;
	}
	printf("ast node type: %d\n", node->type);
	if (node->command != NULL)
	{
		printf("Command list: ");
		print_command_list(node->command);
	}
	if (node->redir != NULL)
	{
		// printf("Redirection list: ");
		print_redir_list(node->redir);
	}
	puts("==========================");
	printf("Left node: \n");
	print_node(node->left);
	printf("Right node\n");
	print_node(node->right);
}