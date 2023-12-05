/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:35:17 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/05 10:18:15 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static t_exit_code	exec_non_bi(const char *command, t_list *args,
						t_exec *config)
{
	pid_t		pid;
	t_exit_code	code;

	config->fork_count++;
	pid = fork();
	if (pid < 0)
		return (operation_failed("fork"), EXIT_KO);
	if (pid == 0)
		exec_non_bi_in_child_process(command, args, config);
	set_exec_handler(true);
	code = single_fork_destructor(pid, config);
	return (code);
}

static t_exit_code	exec_simple_command(t_ast_node *root, t_exec *config)
{
	const char	*command;
	t_list		*args;

	if (!set_expanded_args(root, config))
		exit(EXIT_KO);
	if (config->expanded == NULL)
		return (EXIT_OK);
	command = config->expanded->content;
	args = config->expanded->next;
	if (ft_strcmp(command, "echo") == 0)
		return (bi_echo(args, config));
	if (ft_strcmp(command, "cd") == 0)
		return (bi_cd(args, config));
	if (ft_strcmp(command, "pwd") == 0)
		return (bi_pwd(config));
	if (ft_strcmp(command, "export") == 0)
		return (bi_export(root->command, config));
	if (ft_strcmp(command, "unset") == 0)
		return (bi_unset(args, config));
	if (ft_strcmp(command, "env") == 0)
		return (bi_env(config));
	if (ft_strcmp(command, "exit") == 0)
		return (bi_exit(args, true, config));
	return (exec_non_bi(command, args, config));
}

static	void	exec_simple_command_wrapper(t_ast_node *root, t_exec *config)
{
	int			fd[2];
	int			in;
	int			out;

	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	if (!set_redir(root->redir, &fd, config->env))
		return ((void)(config->exit_code = EXIT_KO));
	if (root->command == NULL)
		return ((void)(config->exit_code = EXIT_OK));
	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	config->exit_code = exec_simple_command(root, config);
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(in);
	close(out);
	if (fd[0] != STDIN_FILENO)
		close(fd[0]);
	if (fd[1] != STDOUT_FILENO)
		close(fd[1]);
}

static void	exec_and_or(t_ast_node *root, t_exec *config)
{
	execute(root->left, config);
	if (root->type == AST_AND)
	{
		if (config->exit_code == EXIT_OK)
			execute(root->right, config);
	}
	if (root->type == AST_OR)
	{
		if (config->exit_code != EXIT_OK)
			execute(root->right, config);
	}
}

void	execute(t_ast_node *root, t_exec *config)
{
	if (root == NULL)
		return ;
	if (root->type == AST_CMD)
		exec_simple_command_wrapper(root, config);
	else if ((root->type == AST_AND) || (root->type == AST_OR))
		exec_and_or(root, config);
	else if (root->type == AST_PIPE)
		exec_pipeline(root, config);
}
