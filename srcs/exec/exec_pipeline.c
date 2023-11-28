/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 01:11:55 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/28 22:01:44 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	exec_in_pipeline(t_ast_node *root, t_exec *config)
{
	char	*expanded_cmd;

	expanded_cmd = expand_variable(root->command->content, config->env);
	if (expanded_cmd == NULL)
		exit(EXIT_KO);
	free(root->command->content);
	root->command->content = expanded_cmd;
	if (ft_strcmp(root->command->content, "echo") == 0)
		exit(bi_echo(root->command->next, config));
	if (ft_strcmp(root->command->content, "cd") == 0)
		exit(bi_cd(root->command->next, config));
	if (ft_strcmp(root->command->content, "pwd") == 0)
		exit(bi_pwd());
	// if (ft_strcmp(root->command->content, "export") == 0)
	// 	exit(bi_export(root->command->next, config));
	if (ft_strcmp(root->command->content, "unset") == 0)
		exit(bi_unset(root->command->next, config));
	if (ft_strcmp(root->command->content, "env") == 0)
		exit(bi_env(config));
	if (ft_strcmp(root->command->content, "exit") == 0)
		exit(bi_exit(root->command->next, false, config));
	else
		exec_non_bi_in_child_process(root->command->content,
			root->command->next, config);
}

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
		dup2(STDOUT_FILENO, fd[1]);
		close(fd[0]);
	}
	if (!set_redir(ast->redir, &fd))
		return (false);
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
	int			len_before;
	int			len_after;

	in = dup(STDIN_FILENO);
	len_before = ft_lstsize(head);
	while (head != NULL)
	{
		ast = head->content;
		if (!pipe_loop(ast, config, head->next == NULL))
			break ;
		head = head->next;
	}
	if (head != NULL)
	{
		len_after = ft_lstsize(head);
		config->fork_count += (len_before - len_after);
		dup2(in, STDIN_FILENO);
		return (false);
	}
	config->fork_count += len_before;
	dup2(in, STDIN_FILENO);
	close(in);
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
	return (pipeline_forks_destructor(config));
}
