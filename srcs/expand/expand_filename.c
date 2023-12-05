/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_filename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 21:01:19 by knishiok          #+#    #+#             */
/*   Updated: 2023/12/05 21:26:39 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static bool	process_file(t_list **res, struct dirent *entry)
{
	char			*filename;
	t_list			*new;

	if (*(entry->d_name) == '.')
		return (true);
	filename = ft_strdup(entry->d_name);
	if (filename == NULL)
		return (ft_lstclear(res, free), operation_failed("malloc"), false);
	new = ft_lstnew(filename);
	if (new == NULL)
		return (ft_lstclear(res, free), operation_failed("malloc"), false);
	ft_lstadd_back(res, new);
	return (true);
}

bool	get_filenames(t_list **res)
{
	DIR				*dir;
	struct dirent	*entry;

	*res = NULL;
	dir = opendir("./");
	if (dir == NULL)
		return (false);
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (!process_file(res, entry))
			return (NULL);
	}
	closedir(dir);
	return (true);
}

t_list	*dup_string_to_list(char *string)
{
	t_list	*res;
	char	*dup_string;

	if (string == NULL)
		return (NULL);
	dup_string = ft_strdup(string);
	if (dup_string == NULL)
		return (operation_failed("malloc"), NULL);
	res = ft_lstnew(dup_string);
	if (res == NULL)
	{
		free(dup_string);
		return (operation_failed("malloc"), NULL);
	}
	return (res);
}
