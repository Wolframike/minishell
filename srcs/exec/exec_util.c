/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:15:01 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/26 19:06:47 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

t_exit_code	exec_non_bi(const char *command, t_list *args, t_exec *config)
{
	pid_t	pid;
	char	**argv;
	char	**envp;

	pid = fork();
	if (pid < 0)
		return (operation_failed("fork"), EXIT_KO);
	if (pid == 0)
	{
		argv = t_list_to_array(command, args);
		envp = env_to_array(config->env);
		if ((argv == NULL) || (envp == NULL))
		{
			free2darr(argv);
			free2darr(envp);
			return (operation_failed("malloc"), EXIT_KO);
		}
		ft_execvp(command, argv, envp);
		free2darr(argv);
		free2darr(envp);
		return (execvp_failed(command));
	}
	return (EXIT_OK);
}
