/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:15:01 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/28 17:12:47 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	exec_non_bi_in_pipeline(const char *command, t_list *args,
		t_exec *config)
{
	char	**argv;
	char	**envp;

	if (!expand_command_list(&args, config->env))
	{
		operation_failed("malloc");
		exit(EXIT_KO);
	}
	argv = t_list_to_array(command, args);
	envp = env_to_array(config->env);
	if ((argv == NULL) || (envp == NULL))
	{
		free2darr(argv);
		free2darr(envp);
		operation_failed("malloc");
		exit(EXIT_KO);
	}
	ft_execvp(command, argv, envp);
	free2darr(argv);
	free2darr(envp);
	execvp_failed(command);
	exit(EXIT_KO);
}

void	exec_in_pipeline(t_ast_node *root, t_exec *config)
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
		exec_non_bi_in_pipeline(root->command->content,
			root->command->next, config);
}

t_exit_code	exec_non_bi(const char *command, t_list *args, t_exec *config)
{
	pid_t	pid;
	char	**argv;
	char	**envp;

	config->fork_count++;
	pid = fork();
	if (pid < 0)
		return (operation_failed("fork"), EXIT_KO);
	if (!expand_command_list(&args, config->env))
		return (operation_failed("malloc"), EXIT_KO);
	if (pid == 0)
	{
		argv = t_list_to_array(command, args);
		envp = env_to_array(config->env);
		if ((argv == NULL) || (envp == NULL))
		{
			free2darr(argv);
			free2darr(envp);
			operation_failed("malloc");
			exit(EXIT_KO);
		}
		ft_execvp(command, argv, envp);
		free2darr(argv);
		free2darr(envp);
		execvp_failed(command);
		exit(EXIT_KO);
	}
	return (EXIT_OK);
}
