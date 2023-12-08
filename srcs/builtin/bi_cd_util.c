/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 23:16:02 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/08 19:47:20 by misargsy         ###   ########.fr       */
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
		return (false);
	if (config->cwd != NULL)
	{
		oldpwd = ft_strdup(config->cwd);
		if (oldpwd == NULL)
			return (operation_failed("malloc"), false);
	}
	if (chdir(target_path) < 0)
		return (free(oldpwd), false);
	return (update_data(oldpwd, config));
}

static bool	move_single_layer(char **goal, const char *layer)
{
	char	*tmp;

	if (ft_strcmp(layer, "..") == 0)
	{
		tmp = ft_strrchr(*goal, '/');
		if (tmp == NULL)
			*goal[0] = '\0';
		else
			*tmp = '\0';
	}
	else if (ft_strcmp(layer, ".") == 0)
		;
	else
	{
		tmp = *goal;
		*goal = ft_strjoin(*goal, "/");
		free(tmp);
		if (*goal == NULL)
			return (false);
		tmp = *goal;
		*goal = ft_strjoin(*goal, layer);
		free(tmp);
	}
	return (true);
}

char	*join_path_and_offset(const char *cwd, const char *target)
{
	char	*goal;
	char	*layer;
	size_t	len;

	goal = ft_strdup(cwd);
	if (goal == NULL)
		return (NULL);
	while (*target != '\0')
	{
		len = 0;
		while (target[len] != '\0' && target[len] != '/')
			len++;
		layer = ft_substr(target, 0, len);
		if (layer == NULL)
			return (free(goal), NULL);
		if (!move_single_layer(&goal, layer))
			return (free(layer), free(goal), NULL);
		free(layer);
		if (goal == NULL)
			return (NULL);
		if (target[len] == '\0')
			break ;
		target += len + 1;
	}
	return (goal);
}
