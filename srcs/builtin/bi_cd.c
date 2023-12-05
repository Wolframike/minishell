/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:18:54 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/05 15:36:42 by misargsy         ###   ########.fr       */
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

static char	*join_path(const char *path, const char *target)
{
	char	*new_path;
	size_t	len;

	if (path == NULL || target == NULL)
		return (NULL);
	len = ft_strlen(path) + ft_strlen(target) + 2;
	new_path = malloc(sizeof(char) * len);
	if (new_path == NULL)
		return (NULL);
	ft_strlcpy(new_path, path, len);
	ft_strlcat(new_path, "/", len);
	ft_strlcat(new_path, target, len);
	return (new_path);
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
		target_path = join_path(config->cwd, args->content);
	if (target_path == NULL && (args == NULL || !ft_strcmp(args->content, "-")))
		return (operation_failed("malloc"), NULL);
	if (target_path == NULL)
		return (general_error(args->content), NULL);
	return (target_path);
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
				error_retrieving_cd("cd");
		}
		else
			if (!is_dir(config->cwd))
				error_retrieving_cd("cd");
	}
	if (args != NULL && ((char *)args->content)[0] == '/')
		target_path = ft_strdup(args->content);
	else
		target_path = set_target_path(args, config);
	if (target_path == NULL)
		return (EXIT_KO);
	if (!move_to_path(target_path, config))
		return (free(target_path), EXIT_KO);
	if (args != NULL && ft_strcmp(args->content, "-") == 0)
		ft_putendl_fd(config->cwd, STDOUT_FILENO);
	return (EXIT_OK);
}
