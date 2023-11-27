/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:35:17 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/27 17:39:06 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static t_exit_code	exec_simple_command(t_ast_node *root, t_exec *config)
{
	if (ft_strcmp(root->command->content, "echo") == 0)
		return (bi_echo(root->command->next, config));
	if (ft_strcmp(root->command->content, "cd") == 0)
		return (bi_cd(root->command->next, config));
	if (ft_strcmp(root->command->content, "pwd") == 0)
		return (bi_pwd());
	// if (ft_strcmp(root->command->content, "export") == 0)
	// 	return (bi_export(root->command->next, config));
	if (ft_strcmp(root->command->content, "unset") == 0)
		return (bi_unset(root->command->next, config));
	if (ft_strcmp(root->command->content, "env") == 0)
		return (bi_env(config));
	if (ft_strcmp(root->command->content, "exit") == 0)
		return (bi_exit(root->command->next, true));
	return (exec_non_bi(root->command->content, root->command->next, config));
}

static	t_exit_code	exec_simple_command_wrapper(t_ast_node *root, t_exec *config)
{
	int	exit_code;
	int	fd[2];
	int	in;
	int	out;

	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	if (!set_redir(root->redir, &fd))
		return (EXIT_KO);
	if (root->command == NULL)
		return (EXIT_OK);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	exit_code = exec_simple_command(root, config);
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(in);
	close(out);
	if (fd[0] != STDIN_FILENO)
		close(fd[0]);
	if (fd[1] != STDOUT_FILENO)
		close(fd[1]);
	return (exit_code);
}

t_exit_code	execute(t_ast_node *root, t_exec *config)
{
	if (root == NULL)
		return (EXIT_OK);
	if (root->type == AST_CMD)
		return (exec_simple_command_wrapper(root, config));
	else if (root->type == AST_AND)
	{
		;// TODO
	}
	else if (root->type == AST_OR)
	{
		;// TODO
	}
	else if (root->type == AST_PIPE)
		return (exec_pipeline(root, config));
	return (EXIT_OK);
}
