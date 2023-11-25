/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 23:16:02 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/25 15:27:51 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <dirent.h>

static	bool	dir_exists(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir == NULL)
		return (false);
	closedir(dir);
	return (true);
}

static void	set_oldpwd(void)
{
	ft_putstr_fd("Set OLDPWD, not implemented yet\n", STDERR_FILENO);
	return ;
	//incomplete
}

static bool	file_name_check(char *path)
{
	size_t	len;
	char	*tmp;

	if (ft_strlen(path) > PATH_MAX)
	{
		file_name_too_long("cd", path);
		return (true);
	}
	len = 0;
	tmp = path;
	while (*tmp != '\0')
	{
		if (*tmp == '/')
			len = 0;
		else
			len++;
		if (len > NAME_MAX)
		{
			file_name_too_long("cd", path);
			return (true);
		}
		tmp++;
	}
	return (false);
}

bool	move_to_envvar(char *varname)
{
	if (getenv(varname) == NULL)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(varname, STDERR_FILENO);
		ft_putstr_fd(" not set\n", STDERR_FILENO);
		return (false);
	}
	if (file_name_check(getenv(varname)))
		return (false);
	if (!dir_exists(getenv(varname)))
	{
		no_such_file_or_directory("cd", getenv(varname));
		return (false);
	}
	set_oldpwd();
	if (chdir(getenv(varname)) < 0)
	{
		operation_failed("chdir");
		return (false);
	}
	return (true);
}

bool	move_to_path(char *path)
{
	if (file_name_check(path))
		return (false);
	if (!dir_exists(path))
	{
		no_such_file_or_directory("cd", path);
		return (false);
	}
	set_oldpwd();
	if (chdir(path) < 0)
	{
		operation_failed("chdir");
		return (false);
	}
	return (true);
}
