/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 23:16:02 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/26 19:01:47 by misargsy         ###   ########.fr       */
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

static bool	set_oldpwd(t_exec *config)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (oldpwd == NULL)
		return (operation_failed("getcwd"), false);
	if (!set_env(config->env, "OLDPWD", oldpwd))
		return (operation_failed("malloc"), false);
	free(oldpwd);
	return (true);
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

bool	move_to_envvar(t_exec *config, char *varname)
{
	char	*path;

	path = get_env(config->env, varname);
	if (path == NULL)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(varname, STDERR_FILENO);
		ft_putstr_fd(" not set\n", STDERR_FILENO);
		return (false);
	}
	if (!dir_exists(path))
	{
		no_such_file_or_directory("cd", path);
		return (false);
	}
	path = ft_strdup(path);
	set_oldpwd(config);
	if (chdir(path) < 0)
	{
		operation_failed("chdir");
		free(path);
		return (false);
	}
	free(path);
	return (true);
}

bool	move_to_path(t_exec *config, char *path)
{
	if (file_name_check(path))
		return (false);
	if (!dir_exists(path))
	{
		no_such_file_or_directory("cd", path);
		return (false);
	}
	set_oldpwd(config);
	if (chdir(path) < 0)
	{
		operation_failed("chdir");
		return (false);
	}
	return (true);
}
