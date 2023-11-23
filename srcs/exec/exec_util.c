/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:15:01 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/23 20:28:26 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

t_exit_code	exec_non_bi(const char *command, t_list *args)
{
	pid_t	pid;
	int		status;
	char	**argv;

	pid = fork();
	if (pid < 0)
		return (operation_failed("fork"), EXIT_KO);
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
