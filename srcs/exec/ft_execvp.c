/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 20:55:48 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/01 14:12:05 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	*get_path_env(char *const *envp)
{
	size_t	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*get_full_path(const char *cmd, char *const *envp)
{
	char	*path;
	char	**path_env;
	char	*dir_candidate;
	size_t	i;

	path = NULL;
	path_env = ft_split(get_path_env(envp), ':');
	if (path_env == NULL)
		return (errno = ENOCMD, NULL);
	i = 0;
	while (path_env[i] != NULL)
	{
		dir_candidate = ft_strjoin(path_env[i], "/");
		path = ft_strjoin(dir_candidate, cmd);
		free(dir_candidate);
		if (path == NULL || access(path, X_OK) == 0)
			break ;
		free(path);
		i++;
	}
	if (path_env[i] == NULL && access(cmd, X_OK) < 0)
		errno = ENOENT;
	free2darr(path_env);
	return (path);
}

int	ft_execvp(const char *file, char *const argv[], char *const *envp)
{
	char	*full_path;

	if (ft_strchr(file, '/') == NULL)
		full_path = get_full_path(file, envp);
	else
	{
		if (is_dir(file))
			return (errno = EISDIR, -1);
		if (access(file, F_OK) < 0)
			return (errno = ENOENT, -1);
		if (access(file, X_OK) < 0)
			return (errno = EACCES, -1);
		full_path = ft_strdup(file);
	}
	if (full_path == NULL)
		return (-1);
	return (execve(full_path, argv, envp));
}

char	**t_list_to_array(const char *command, t_list *lst)
{
	char	**arr;
	size_t	i;

	arr = (char **)malloc(sizeof(char *) * (ft_lstsize(lst) + 2));
	if (arr == NULL)
		return (NULL);
	i = 0;
	arr[i] = ft_strdup(command);
	if (arr[i++] == NULL)
		return (free(arr), NULL);
	while (lst != NULL)
	{
		arr[i] = ft_strdup(lst->content);
		if (arr[i] == NULL)
		{
			free2darr(arr);
			return (NULL);
		}
		i++;
		lst = lst->next;
	}
	arr[i] = NULL;
	return (arr);
}
