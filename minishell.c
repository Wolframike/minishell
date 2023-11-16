/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:37:40 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/16 16:34:32 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_cmd(char *command, char **envp)
{
	char	**command_exec;
	size_t	i;

	command_exec = ft_split(command, ' ');
	if (command_exec == NULL)
		spit_error(false, "malloc");
	if (command_exec[0] == NULL)
		spit_error(false, "command not found");
	if (command_exec[0][0] != '/')
		command_exec[0] = get_path(command_exec[0], envp);
	i = 0;
	if (command_exec[0] == NULL)
	{
		while (command_exec[i] != NULL)
			free(command_exec[i++]);
		free(command_exec);
		spit_error(false, "command not found");
	}
	execve(command_exec[0], command_exec, envp);
}

static void	handle_line(char *line, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		spit_error(false, "fork");
	if (pid == 0)
	{
		exec_cmd(line, envp);
		exit(EXIT_SUCCESS);
	}
	else
		waitpid(pid, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argc;
	(void)argv;
	rl_outstream = stderr;
	while (true)
	{
		line = readline(PROMPT);
		if (ft_strcmp(line, "exit") == 0)
		{
			free(line);
			ft_putstr_fd("exit\n", STDERR_FILENO);
			break ;
		}
		handle_line(line, envp);
		free(line);
	}
	exit(EXIT_SUCCESS);
}
