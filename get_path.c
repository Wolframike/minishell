/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:21:20 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/15 16:00:10 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strndup(const char *src, size_t n)
{
	char	*dest;
	size_t	l;

	l = ft_strlen(src);
	if (n < l)
		l = n;
	dest = (char *)malloc(sizeof(char) * (l + 1));
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, src, l + 1);
	return (dest);
}

static char	*find_dir(char *command, char *path)
{
	size_t	i;
	char	*cmddir;
	char	*cmdpath;

	i = 0;
	while (path[i] != ':' && path[i] != '\0')
		i++;
	if (i == 0)
		return (NULL);
	cmddir = ft_strndup(path, i + 1);
	if (cmddir == NULL)
		spit_error(false, "malloc");
	cmddir[i] = '/';
	cmdpath = ft_strjoin(cmddir, command);
	free(cmddir);
	if (cmdpath == NULL)
		spit_error(false, "malloc");
	if (access(cmdpath, X_OK) == 0)
		return (cmdpath);
	free(cmdpath);
	return (NULL);
}

static char	*format_env(char **envp)
{
	char	*path;
	size_t	i;

	i = 0;
	path = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			path = envp[i] + 5;
		i++;
	}
	path = ft_strjoin(path, ":");
	return (path);
}

char	*get_path(char *command, char **envp)
{
	char	*path;
	char	*cmdpath;

	if (command[0] == '.')
	{
		if ((access(command, F_OK) != 0))
			spit_error(false, command);
		if (access(command, X_OK) != 0)
			spit_error(false, command);
		return (command);
	}
	path = format_env(envp);
	if (path == NULL)
		spit_error(false, command);
	cmdpath = NULL;
	while (*path != '\0')
	{
		cmdpath = find_dir(command, path);
		if (cmdpath != NULL)
			return (cmdpath);
		while (*path != ':' && *path != '\0')
			path++;
		path += (*path == ':');
	}
	return (cmdpath);
}
