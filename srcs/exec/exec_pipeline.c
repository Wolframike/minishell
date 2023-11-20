/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 01:11:55 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/21 03:40:10 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static	bool	create_pipeline_list(t_ast_node *root, t_list **head)
{
	t_list	*new;

	(*head) = ft_lstnew(root->right);
	if ((*head) == NULL)
		return (false);
	while (root->right != NULL)
	{
		new = ft_lstnew(root->right);
		if (new == NULL)
			return (false);
		ft_lstadd_front((*head), new);
		root = root->right;
	}
	return (true);
}

static bool	pipe_loop(t_ast_node *node, bool last)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		return (operation_failed("pipe"), false);
	pid = fork();
	if (pid < 0)
		return (operation_failed("fork"), false);
	//incomplete
}

static void	exec_pipeline_list(t_list *head)
{
	while (head != NULL)
	{
		pipe_loop(head->content, head->next == NULL);
		head = head->next;
	}
}

t_exit_code	exec_pipeline(t_ast_node *root)
{
	t_list	*head;

	if (root == NULL)
		return (EXIT_OK);
	if (!create_pipeline_list(root, &head))
	{
		while (head != NULL)
		{
			free(head->content);
			head = head->next;
		}
		return (operation_failed("malloc"), EXIT_KO);
	}
	//incomplete
}
