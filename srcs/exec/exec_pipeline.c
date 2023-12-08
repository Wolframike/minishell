/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 01:11:55 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/08 20:57:18 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static bool	create_pipeline_list(t_ast_node *root, t_list **head)
{
	t_list	*new;

	while (root->type == AST_PIPE)
	{
		new = ft_lstnew(root->right);
		if (new == NULL)
			return (false);
		ft_lstadd_front(head, new);
		root = root->left;
	}
	new = ft_lstnew(root);
	if (new == NULL)
		return (false);
	ft_lstadd_front(head, new);
	return (true);
}

void	exec_pipeline(t_ast_node *root, t_exec *config)
{
	t_list	*head;

	if (root == NULL)
	{
		config->exit_code = EXIT_OK;
		return ;
	}
	head = NULL;
	if (!create_pipeline_list(root, &head))
	{
		ft_lstclear(&head, NULL);
		config->exit_code = EXIT_KO;
		return (operation_failed("malloc"));
	}
	if (!exec_pipeline_list(head, config))
	{
		ft_lstclear(&head, NULL);
		config->exit_code = EXIT_KO;
		return ;
	}
	ft_lstclear(&head, NULL);
	config->exit_code = pipeline_forks_destructor(config);
}
