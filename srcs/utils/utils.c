/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:31:04 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/28 22:50:47 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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

bool	dir_exists(const char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir == NULL)
		return (false);
	closedir(dir);
	return (true);
}
