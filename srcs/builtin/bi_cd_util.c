/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 23:16:02 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/05 14:26:46 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	update_data(char *oldpwd, t_exec *config)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (operation_failed("getcwd"), false);
	if (set_env(&config->env, "PWD", cwd) == false)
		return (free(cwd), operation_failed("malloc"), false);
	free(config->cwd);
	config->cwd = cwd;
	if (set_env(&config->env, "OLDPWD", oldpwd) == false)
		return (operation_failed("malloc"), false);
	free(oldpwd);
	return (true);
}

static bool	filename_check(const char *path)
{
	size_t		len;
	const char	*tmp;

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

bool	move_to_path(const char *target_path, t_exec *config)
{
	char	*oldpwd;

	if (filename_check(target_path))
		return (false);
	if (!is_dir(target_path))
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd((char *)target_path, STDERR_FILENO);
		if (errno == ENOTDIR)
			ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
		if (errno == ENOENT)
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		if (errno == EACCES)
			ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		return (false);
	}
	if (config->cwd != NULL)
	{
		oldpwd = ft_strdup(config->cwd);
		if (oldpwd == NULL)
			return (operation_failed("malloc"), false);
	}
	if (chdir(target_path) < 0)
		return (free(oldpwd), operation_failed("chdir"), false);
	return (update_data(oldpwd, config));
}
