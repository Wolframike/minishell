/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 20:56:52 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/09 18:24:13 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	init_exec_in_pipeline(t_ast_node *root, t_exec *config)
{
	if (root->type == AST_SUBSHELL)
	{
		exec_subshell(root, config);
		exit(config->exit_code);
	}
	if (!set_expanded_args(root, config))
		exit(EXIT_KO);
	if (config->expanded == NULL)
		exit(EXIT_OK);
}

static void	exec_in_pipeline(t_ast_node *root, t_exec *config)
{
	const char	*command;
	t_list		*args;

	init_exec_in_pipeline(root, config);
	command = config->expanded->content;
	args = config->expanded->next;
	if (ft_strcmp(command, "echo") == 0)
		exit(bi_echo(args, config));
	if (ft_strcmp(command, "cd") == 0)
		exit(bi_cd(args, config));
	if (ft_strcmp(command, "pwd") == 0)
		exit(bi_pwd(config));
	if (ft_strcmp(command, "export") == 0)
		exit(bi_export(root->command, config));
	if (ft_strcmp(command, "unset") == 0)
		exit(bi_unset(args, config));
	if (ft_strcmp(command, "env") == 0)
		exit(bi_env(config));
	if (ft_strcmp(command, "exit") == 0)
		exit(bi_exit(args, false, config));
	exec_non_bi_in_child_process(command, args, config);
}

static bool	pipe_loop(t_ast_node *ast, t_exec *config, bool last)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) < 0)
		return (operation_failed("pipe"), false);
	pid = fork();
	if (last)
		dup2(STDOUT_FILENO, fd[1]);
	if (pid < 0)
		return (operation_failed("fork"), false);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (!set_redir(ast->redir, config->env))
			exit(EXIT_KO);
		exec_in_pipeline(ast, config);
	}
	config->pids[config->fork_count] = pid;
	config->fork_count++;
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	return (true);
}

bool	exec_pipeline_list(t_list *head, t_exec *config)
{
	t_ast_node	*ast;
	int			in;
	int			out;

	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	while (head != NULL)
	{
		ast = head->content;
		if (!pipe_loop(ast, config, head->next == NULL))
			break ;
		head = head->next;
	}
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(in);
	close(out);
	return (head == NULL);
}
