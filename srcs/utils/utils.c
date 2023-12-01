/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:31:04 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/01 14:06:46 by misargsy         ###   ########.fr       */
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

bool	is_dir(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) < 0)
		return (operation_failed("stat"), false);
	return (S_ISDIR(statbuf.st_mode));
}
