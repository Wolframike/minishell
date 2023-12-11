/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 21:24:22 by knishiok          #+#    #+#             */
/*   Updated: 2023/12/11 11:10:33 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static bool	contain_expansion(char *pattern, bool *malloc_flg)
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

static bool	handle_no_match(t_list **res, char *pattern)
{
	*res = dup_string_to_list(pattern);
	if (*res == NULL)
		return (false);
	return (true);
}

static bool	expand_filename(t_list **res, char *pattern)
{
	t_list	*head;
	t_list	*dir_filenames;
	bool	malloc_flg;

	malloc_flg = false;
	if (!contain_expansion(pattern, &malloc_flg) && !malloc_flg)
		return (true);
	if (malloc_flg)
		return (NULL);
	*res = NULL;
	if (!get_filenames(&dir_filenames))
		return (handle_no_match(res, pattern));
	if (dir_filenames == NULL)
		return (true);
	head = dir_filenames;
	while (dir_filenames)
	{
		if (matched(dir_filenames->content, pattern, &malloc_flg))
			if (!merge_list(dir_filenames->content, malloc_flg, res))
				return (false);
		dir_filenames = dir_filenames->next;
	}
	ft_lstclear(&head, free);
	return (true);
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
		new = NULL;
		if (ft_strchr((*input)->content, '*') != NULL)
			if (!expand_filename(&new, (*input)->content))
				return (ft_lstclear(&head, free),
					operation_failed("malloc"), NULL);
		if (new == NULL)
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
