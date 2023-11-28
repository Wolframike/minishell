/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 01:28:00 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/28 18:56:40 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "execute.h"

t_exit_code	execvp_failed(const char *command)
{
	if (errno == ENOENT)
	{
		if (ft_strchr(command, '/') == NULL)
			command_not_found(command);
		else
			operation_failed(command);
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
