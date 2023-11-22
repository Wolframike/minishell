/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:35:17 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/22 20:43:41 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static t_exit_code	exec_non_bi(const char *command, t_list *args)
{
	pid_t	pid;
	int		status;
	char	**argv;

	pid = fork();
	if (pid < 0)
		return (EXIT_KO);
	if (pid == 0)
	{
		argv = t_list_to_char_arr(command, args);
		ft_execvp(command, argv);
		free2darr(argv);
		return (execvp_failed(command));
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_KO);
}

static t_exit_code	exec_simple_command(t_ast_node *root)
{
	if (ft_strcmp(root->command->content, "echo") == 0)
		return (bi_echo(root->command->next));
	// if (ft_strcmp(root->command->content, "cd") == 0)
	// 	return (bi_cd(root->command->next));
	if (ft_strcmp(root->command->content, "pwd") == 0)
		return (bi_pwd());
	// if (ft_strcmp(root->command->content, "export") == 0)
	// 	return (bi_export(root->command->next));
	// if (ft_strcmp(root->command->content, "unset") == 0)
	// 	return (bi_unset(root->command->next));
	// if (ft_strcmp(root->command->content, "env") == 0)
	// 	return (bi_env(root->command->next));
	if (ft_strcmp(root->command->content, "exit") == 0)
		return (bi_exit(root->command->next, true));
	return (exec_non_bi(root->command->content, root->command->next));
}

static	t_exit_code	exec_simple_command_wrapper(t_ast_node *root)
{
	int	exit_code;
	int	fd[2];
	int	in;
	int	out;

	if (!set_redir(root->redir, &fd))
		return (EXIT_KO);
	if (root->command == NULL)
		return (EXIT_OK);
	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	exit_code = exec_simple_command(root);
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(in);
	close(out);
	close(fd[0]);
	close(fd[1]);
	return (exit_code);
}

t_exit_code	execute(t_ast_node *root)
{
	if (root == NULL)
		return (EXIT_OK);
	if (root->type == AST_CMD)
		return (exec_simple_command_wrapper(root));
	else if (root->type == AST_AND)
	{
		if (execute(root->left) == EXIT_KO)
			return (execute(root->right));
	}
	else if (root->type == AST_OR)
	{
		if (execute(root->left) == EXIT_KO)
			return (execute(root->right));
	}
	// else if (root->type == AST_PIPE)
	// 	return (exec_pipeline(root));
	return (EXIT_OK);
}
