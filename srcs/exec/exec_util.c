/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:15:01 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/09 18:30:53 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	exec_non_bi_in_child_process(const char *command, t_list *args,
		t_exec *config)
{
	char	**argv;
	char	**envp;

	set_exec_child_handler();
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
	exit(execvp_failed(command));
}

bool	set_expanded_args(t_ast_node *root, t_exec *config)
{
	if (config->expanded != NULL)
		ft_lstclear(&config->expanded, free);
	if (!expand_command_list(root->command, config->env, &config->expanded))
		return (false);
	return (true);
}

t_exit_code	single_fork_destructor(pid_t pid, t_exec *config)
{
	int	status;

	if (config->fork_count != 0)
	{
		config->fork_count = 0;
		if (waitpid(pid, &status, 0) < 0)
			waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
			return (WTERMSIG(status) + 128);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (EXIT_KO);
}

t_exit_code	pipeline_forks_destructor(t_exec *config)
{
	int		status;
	pid_t	pid;
	size_t	i;

	i = 0;
	while (config->fork_count > 0)
	{
		pid = config->pids[i++];
		if (waitpid(pid, &status, 0) < 0)
			waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGPIPE)
				config->exit_code = 127;
			else
				config->exit_code = WTERMSIG(status) + 128;
		}
		if (WIFEXITED(status))
			config->exit_code = WEXITSTATUS(status);
		status = 0;
		config->fork_count--;
	}
	free(config->pids);
	config->pids = NULL;
	return (config->exit_code);
}
