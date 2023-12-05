/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 15:21:39 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/05 14:30:05 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	bi_pwd(t_exec *config)
{
	char	*cwd;

	if (config->cwd == NULL)
	{
		cwd = getcwd(NULL, 0);
		if (cwd == NULL)
		{
			if (errno == EACCES || errno == ENOENT || errno == ENOTDIR)
				error_retrieving_cd("pwd");
			else
				operation_failed("getcwd");
			return (EXIT_KO);
		}
		free(config->cwd);
		config->cwd = cwd;
	}
	ft_putendl_fd(config->cwd, STDOUT_FILENO);
	return (EXIT_OK);
}
