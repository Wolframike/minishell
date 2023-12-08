/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 01:28:00 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/07 22:36:02 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

static void	is_a_directory(const char *command)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd((char *)command, STDERR_FILENO);
	ft_putendl_fd(": is a directory", STDERR_FILENO);
}

void	ambiguous_redirect(const char *filename)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd((char *)filename, STDERR_FILENO);
	ft_putendl_fd(": ambiguous redirect", STDERR_FILENO);
}

t_exit_code	execvp_failed(const char *command)
{
	if (errno == ENOCMD)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd((char *)command, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (EXIT_NOENT);
	}
	else if (errno == ENOENT)
	{
		if (ft_strchr(command, '/') == NULL)
			command_not_found(command);
		else
			operation_failed(command);
		return (EXIT_NOENT);
	}
	else if (errno == ENOMEM)
		return (operation_failed("malloc"), EXIT_KO);
	else if (errno == EISDIR)
		return (is_a_directory(command), EXIT_EXEC);
	else
		return (operation_failed(command), EXIT_KO);
}
