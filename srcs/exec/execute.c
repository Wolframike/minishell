/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:35:17 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/21 01:11:46 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static t_exit_code	exec_non_bi(const char *cmd, t_list *args)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (EXIT_KO);
	if (pid == 0)
	{
		ft_execvp(cmd, args);
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		return (EXIT_NOENT);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_KO);
}

static t_exit_code	exec_simple_command(t_ast_node *root)
{
	if (root->value == NULL)
		return (EXIT_OK);
	if (ft_strcmp(root->value->value, "echo") == 0)
		return (bi_echo(root->value->next));
	// if (ft_strcmp(root->value->value, "cd") == 0)
	// 	return (bi_cd(root->value->next));
	if (ft_strcmp(root->value->value, "pwd") == 0)
		return (bi_pwd());
	// if (ft_strcmp(root->value->value, "export") == 0)
	// 	return (bi_export(root->value->next));
	// if (ft_strcmp(root->value->value, "unset") == 0)
	// 	return (bi_unset(root->value->next));
	// if (ft_strcmp(root->value->value, "env") == 0)
	// 	return (bi_env(root->value->next));
	if (ft_strcmp(root->value->value, "exit") == 0)
		return (bi_exit(root->value->next, false));
	return (exec_non_bi(root->value->value, root->value->next));
}

t_exit_code	execute(t_ast_node *root)
{
	if (root == NULL)
		return (EXIT_OK);
	if (root->type == AST_COMMAND)
		return (exec_simple_command(root));
	else if (root->type == AST_AND)
		if (execute(root->left) == EXIT_KO)
			return (execute(root->right));
	else if (root->type == AST_OR)
		if (execute(root->left) == EXIT_KO)
			return (execute(root->right));
	else if (root->type == AST_PIPE)
		return (exec_pipeline(root));
}
