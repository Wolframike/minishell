/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:31:04 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/11 11:05:13 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

bool	strdup_case_null(char **res, const char *src)
{
	if (src == NULL)
		*res = ft_strdup("");
	else
		*res = ft_strdup(src);
	if (*res == NULL)
		return (false);
	return (true);
}

void	free2darr(char **arr)
{
	size_t	i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
}

bool	is_dir(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) < 0)
		return (false);
	if (S_ISREG(statbuf.st_mode))
		errno = ENOTDIR;
	return (S_ISDIR(statbuf.st_mode));
}

bool	judge_executable(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_strchr(" \n\t", line[i]) == NULL)
			return (true);
		i++;
	}
	return (false);
}
