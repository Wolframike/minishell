/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:18:54 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/28 16:08:21 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <dirent.h>

int	bi_cd(t_list *args, t_exec *config)
{
	char	*pwd;

	if (args == NULL)
	{
		if (!move_to_envvar(config, "HOME"))
			return (EXIT_KO);
		return (EXIT_OK);
	}
	if (ft_strcmp(args->content, "-") == 0)
	{
		if (!move_to_envvar(config, "OLDPWD"))
			return (EXIT_KO);
		pwd = getcwd(NULL, 0);
		if (pwd == NULL)
			return (operation_failed("getcwd"), EXIT_KO);
		ft_putendl_fd(pwd, STDOUT_FILENO);
		free(pwd);
		return (EXIT_OK);
	}
	else
	{
		if (!move_to_path(config, args->content))
			return (EXIT_KO);
		return (EXIT_OK);
	}
}
