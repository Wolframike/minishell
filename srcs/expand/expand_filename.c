/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_filename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 21:01:19 by knishiok          #+#    #+#             */
/*   Updated: 2023/12/05 20:16:33 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static bool	get_filenames(t_list **res)
{
	t_list			*new;
	char			*filename;
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
		if (*(entry->d_name) == '.')
			continue ;
		filename = ft_strdup(entry->d_name);
		if (filename == NULL)
			return (ft_lstclear(res, free), operation_failed("malloc"), NULL);
		new = ft_lstnew(filename);
		if (new == NULL)
			return (ft_lstclear(res, free), operation_failed("malloc"), NULL);
		ft_lstadd_back(res, new);
	}
	closedir(dir);
	return (true);
}

static bool	merge_list(char *filename, bool flg, t_list **res)
{
	t_list	*new;
	char	*content;

	if (flg)
		return (ft_lstclear(res, free), operation_failed("malloc"), false);
	content = ft_strdup(filename);
	if (content == NULL)
		return (ft_lstclear(res, free), operation_failed("malloc"), false);
	new = ft_lstnew(content);
	if (new == NULL)
		return (ft_lstclear(res, free), operation_failed("malloc"), false);
	ft_lstadd_back(res, new);
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

bool	contain_expansion(char *pattern, bool *malloc_flg)
{
	int		pat_len;
	bool	*pat_exp;

	pat_len = count_patlen(pattern);
	pat_exp = expand_or_not(pattern);
	if (pat_exp == NULL)
	{
		*malloc_flg = true;
		return (operation_failed("malloc"), NULL);
	}
	while (--pat_len >= 0)
	{
		if (pat_exp[pat_len])
		{
			free(pat_exp);
			return (true);
		}
	}
	free(pat_exp);
	return (false);
}

static t_list	*expand_filename(char *pattern)
{
	t_list	*head;
	t_list	*dir_filenames;
	t_list	*res;
	bool	malloc_flg;

	malloc_flg = false;
	if (!contain_expansion(pattern, &malloc_flg) && !malloc_flg)
		return (dup_string_to_list(pattern));
	if (malloc_flg)
		return (NULL);
	res = NULL;
	if (!get_filenames(&dir_filenames))
		return (dup_string_to_list(pattern));
	if (dir_filenames == NULL)
		return (NULL);
	head = dir_filenames;
	while (dir_filenames)
	{
		if (matched(dir_filenames->content, pattern, &malloc_flg))
		{
			if (!merge_list(dir_filenames->content, malloc_flg, &res))
				return (NULL);
		}
		dir_filenames = dir_filenames->next;
	}
	ft_lstclear(&head, free);
	return (res);
}

t_list	*expand_wildcard(t_list **input)
{
	t_list	*res;
	t_list	*new;
	t_list	*head;

	if (input == NULL || *input == NULL)
		return (NULL);
	res = NULL;
	head = *input;
	while (*input)
	{
		if (ft_strchr((*input)->content, '*') != NULL)
			new = expand_filename((*input)->content);
		else
			new = dup_string_to_list((*input)->content);
		if (new == NULL)
			return (ft_lstclear(&res, free),
				ft_lstclear(&head, free), NULL);
		ft_lstadd_back(&res, new);
		*input = (*input)->next;
	}
	ft_lstclear(&head, free);
	return (res);
}
