/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 20:55:48 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/20 21:42:54 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	free2darr(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
}

static char	*get_full_path(const char *cmd)
{
	char	*path;
	char	**path_env;
	char	*dir_candidate;
	size_t	i;

	path = NULL;
	path_env = ft_split(getenv("PATH"), ':');
	i = 0;
	while (path_env[i] != NULL)
	{
		dir_candidate = ft_strjoin(path_env[i], "/");
		path = ft_strjoin(dir_candidate, cmd);
		free(dir_candidate);
		if ((path == NULL) || (access(path, X_OK)) == 0)
			break ;
		free(path);
		i++;
	}
	free2darr(path_env);
	return (path);
}

int	ft_execvp(const char *file, char *const argv[])
{
	char	*full_path;

	if (ft_strchr(file, '/') == NULL)
		full_path = get_full_path(file);
	else
		full_path = ft_strdup(file);
	if (full_path == NULL)
		return (-1);
	return (execve(full_path, argv, environ));
}
