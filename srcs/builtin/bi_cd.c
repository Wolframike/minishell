/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:18:54 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/09 19:14:55 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <dirent.h>

static void	not_set(const char *varname)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd((char *)varname, STDERR_FILENO);
	ft_putstr_fd(" not set\n", STDERR_FILENO);
}

static void	general_error(const char *path)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd((char *)path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

static char	*set_target_path(t_list *args, t_exec *config)
{
	char	*target_path;
	char	*home;
	char	*oldpwd;

	if (args == NULL)
	{
			home = get_env(config->env, "HOME");
		if (home == NULL)
			return (not_set("HOME"), NULL);
		target_path = ft_strdup(home);
	}
	else if (ft_strcmp(args->content, "-") == 0)
	{
		oldpwd = get_env(config->env, "OLDPWD");
		if (oldpwd == NULL)
			return (not_set("OLDPWD"), NULL);
		target_path = ft_strdup(oldpwd);
	}
	else
		target_path = join_path_and_offset(config->cwd, args->content);
	if (target_path == NULL && (args == NULL || !ft_strcmp(args->content, "-")))
		return (operation_failed("malloc"), NULL);
	if (target_path == NULL)
		return (general_error(args->content), NULL);
	return (target_path);
}

static void	print_error(const char *path, const char *cwd)
{
	if (errno == ENOENT && !is_dir(cwd))
	{
		error_retrieving_cd("cd");
		return ;
	}
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd((char *)path, STDERR_FILENO);
	if (errno == ENOTDIR)
		ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
	if (errno == ENOENT)
	{
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	}
	if (errno == EACCES)
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
}

int	bi_cd(t_list *args, t_exec *config)
{
	char	*target_path;

	if (args != NULL && ((char *)args->content)[0] != '/')
	{
		if (config->cwd == NULL)
		{
			config->cwd = getcwd(NULL, 0);
			if (config->cwd == NULL)
				return (error_retrieving_cd("cd"), EXIT_OK);
		}
	}
	if (args != NULL && ((char *)args->content)[0] == '/')
		target_path = ft_strdup(args->content);
	else
		target_path = set_target_path(args, config);
	if (target_path == NULL)
		return (EXIT_KO);
	if (!move_to_path(target_path, config))
		return (print_error(target_path, config->cwd),
			free(target_path), EXIT_KO);
	if (args != NULL && ft_strcmp(args->content, "-") == 0)
		ft_putendl_fd(config->cwd, STDOUT_FILENO);
	return (free(target_path), EXIT_OK);
}
