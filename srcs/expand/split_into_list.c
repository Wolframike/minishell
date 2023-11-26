/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_into_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 17:35:08 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/26 19:00:30 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void	set_res(t_list **res, char *line)
{
	char	*str;

	*res = NULL;
	if (*line == '\0')
	{
		str = ft_strdup("");
		if (str == NULL)
			return (operation_failed("malloc"));
		*res = ft_lstnew(str);
		if (*res == NULL)
			return (operation_failed("malloc"));
	}
}

static t_list	*split_line_to_list(char *line)
{
	t_list	*res;
	t_list	*new;
	char	*word_start;
	char	*chunk;

	set_res(&res, line);
	while (*line)
	{
		if (ft_strchr(" \n\t", *line) == NULL)
		{
			word_start = line;
			while (*line && ft_strchr(" \n\t", *line) == NULL)
				line++;
			chunk = ft_strndup(word_start, line - word_start);
			if (chunk == NULL)
				return (ft_lstclear(&res, free), NULL);
			new = ft_lstnew(chunk);
			if (new == NULL)
				return (ft_lstclear(&res, free), NULL);
			ft_lstadd_back(&res, new);
		}
		else
			line++;
	}
	return (res);
}

t_list	*expand_variable_list(char *line, t_env *env)
{
	t_list	*res;
	char	*expanded;

	expanded = expand_variable(line, env);
	if (expanded == NULL)
		return (NULL);
	res = split_line_to_list(expanded);
	free(expanded);
	if (res == NULL)
		return (operation_failed("malloc"), NULL);
	return (res);
}
