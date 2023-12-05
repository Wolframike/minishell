/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:32:44 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/05 14:20:58 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

void	too_many_arguments(const char *command)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd((char *)command, STDERR_FILENO);
	ft_putstr_fd(": too many arguments\n", STDERR_FILENO);
}

void	file_name_too_long(const char *command, const char *path)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd((char *)command, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd((char *)path, STDERR_FILENO);
	ft_putstr_fd(": File name too long\n", STDERR_FILENO);
}

void	not_a_valid_identifier(const char *command, const char *arg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd((char *)command, STDERR_FILENO);
	ft_putstr_fd(": `", STDERR_FILENO);
	ft_putstr_fd((char *)arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

void	error_retrieving_cd(const char *operation)
{
	ft_putstr_fd((char *)operation, STDERR_FILENO);
	ft_putstr_fd(": error retrieving current directory: getcwd", STDERR_FILENO);
	ft_putstr_fd(": cannot access parent directories: ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
}
