/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 01:28:00 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/22 19:42:01 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	command_not_found(const char *command)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd((char *)command, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
}

void	permission_denied(const char *filename)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd((char *)filename, STDERR_FILENO);
	ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
}

void	operation_failed(const char *operation)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd((char *)operation, STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
}

t_exit_code	execvp_failed(const char *command)
{
	if (errno == ENOENT)
	{
		command_not_found(command);
		return (EXIT_NOENT);
	}
	else if (errno == ENOMEM)
	{
		operation_failed("malloc");
		return (EXIT_KO);
	}
	else
	{
		operation_failed("execve");
		return (EXIT_KO);
	}
}
