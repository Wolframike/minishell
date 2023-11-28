/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 01:11:55 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/28 17:14:31 by misargsy         ###   ########.fr       */
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

static bool	pipe_loop(t_ast_node *ast, t_exec *config, bool last)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) < 0)
		return (operation_failed("pipe"), false);
	if (last)
	{
		close(fd[1]);
		dup2(STDOUT_FILENO, fd[1]);
	}
	if (!set_redir(ast->redir, &fd))
		return (false);
	config->fork_count++;
	pid = fork();
	if (pid < 0)
		return (operation_failed("fork"), false);
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
		exec_in_pipeline(ast, config);
	}
	dup2(fd[0], STDIN_FILENO);
	return (close(fd[0]), close(fd[1]), true);
}

static bool	exec_pipeline_list(t_list *head, t_exec *config)
{
	t_ast_node	*ast;
	int			in;

	in = dup(STDIN_FILENO);
	while (head != NULL)
	{
		ast = head->content;
		if (!pipe_loop(ast, config, head->next == NULL))
			return (false);
		head = head->next;
	}
	dup2(in, STDIN_FILENO);
	return (true);
}

t_exit_code	exec_pipeline(t_ast_node *root, t_exec *config)
{
	t_list	*head;

	if (root == NULL)
		return (EXIT_OK);
	head = NULL;
	if (!create_pipeline_list(root, &head))
	{
		ft_lstclear(&head, NULL);
		return (operation_failed("malloc"), EXIT_KO);
	}
	if (!exec_pipeline_list(head, config))
	{
		ft_lstclear(&head, NULL);
		return (EXIT_KO);
	}
	ft_lstclear(&head, NULL);
	return (EXIT_OK);
}
