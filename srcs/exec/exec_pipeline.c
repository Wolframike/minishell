/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 01:11:55 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/23 20:49:06 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	exec_simple_command_for_pipeline(t_ast_node *root)
{
	if (ft_strcmp(root->command->content, "echo") == 0)
		exit(bi_echo(root->command->next));
	// if (ft_strcmp(root->command->content, "cd") == 0)
	// 	return (bi_cd(root->command->next));
	if (ft_strcmp(root->command->content, "pwd") == 0)
		exit(bi_pwd());
	// if (ft_strcmp(root->command->content, "export") == 0)
	// 	exit(bi_export(root->command->next));
	// if (ft_strcmp(root->command->content, "unset") == 0)
	// 	exit(bi_unset(root->command->next));
	// if (ft_strcmp(root->command->content, "env") == 0)
	// 	exit(bi_env(root->command->next));
	if (ft_strcmp(root->command->content, "exit") == 0)
		exit(bi_exit(root->command->next, false));
	exit(exec_non_bi(root->command->content, root->command->next));
}

static bool	create_pipeline_list(t_ast_node *root, t_list **head)
{
	t_list	*new;

	(*head) = ft_lstnew(root->right);
	if ((*head) == NULL)
		return (false);
	while (root->left->type == AST_PIPE)
	{
		new = ft_lstnew(root->right);
		if (new == NULL)
			return (false);
		ft_lstadd_front(head, new);
		root = root->left;
	}
	new = ft_lstnew(root->left);
	if (new == NULL)
		return (false);
	ft_lstadd_front(head, new);
	return (true);
}

static bool	pipe_loop(t_ast_node *ast, t_list *redirects, bool last)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) < 0)
		return (operation_failed("pipe"), false);
	pid = fork();
	if (pid < 0)
		return (operation_failed("fork"), false);
	if (!set_redir(redirects, &fd))
		return (false);
	if (pid == 0 && last)
	{
		close(fd[1]);
		dup2(STDOUT_FILENO, fd[1]);
	}
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
		exec_simple_command_for_pipeline(ast);
	}
	dup2(fd[0], STDIN_FILENO);
	return (close(fd[0]), close(fd[1]), true);
}

static bool	exec_pipeline_list(t_list *head, t_list *redirects)
{
	t_ast_node	*ast;
	int			in;

	in = dup(STDIN_FILENO);
	while (head != NULL)
	{
		ast = head->content;
		if (!pipe_loop(ast, redirects, head->next == NULL))
			return (false);
		head = head->next;
	}
	dup2(in, STDIN_FILENO);
	return (true);
}

t_exit_code	exec_pipeline(t_ast_node *root)
{
	t_list	*head;

	if (root == NULL)
		return (EXIT_OK);
	if (!create_pipeline_list(root, &head))
	{
		ft_lstclear(&head, NULL);
		return (operation_failed("malloc"), EXIT_KO);
	}
	if (!exec_pipeline_list(head, root->redir))
	{
		ft_lstclear(&head, NULL);
		return (EXIT_KO);
	}
	while (head != NULL)
	{
		wait(NULL);
		head = head->next;
	}
	ft_lstclear(&head, NULL);
	return (EXIT_OK);
}