/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 21:08:48 by knishiok          #+#    #+#             */
/*   Updated: 2023/12/05 21:10:19 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

t_list	*remove_quotes(char *line)
{
	t_list	*res;
	char	*res_str;

	res_str = ft_strdup("");
	if (res_str == NULL)
		return (NULL);
	while (*line)
	{
		if (*line == '\'' || *line == '\"')
			line++;
		else
		{
			if (!skip_line(&line, res_str, &res_str))
				return (free(res_str), NULL);
		}
	}
	res = ft_lstnew(res_str);
	if (res == NULL)
		return (free(res_str), NULL);
	return (res);
}

bool	handle_quote(t_list **res, char **line)
{
	char	*word_start;
	char	*chunk;
	t_list	*new;

	word_start = *line;
	if (*word_start == '\'' || *word_start == '\"')
	{
		(*line)++;
		while (**line && **line != *word_start)
			(*line)++;
		if (**line == *word_start)
			(*line)++;
	}
	while (**line && ft_strchr(" \n\t", **line) == NULL)
		(*line)++;
	chunk = ft_strndup(word_start, *line - word_start);
	if (chunk == NULL)
		return (ft_lstclear(res, free), false);
	new = ft_lstnew(chunk);
	if (new == NULL)
		return (ft_lstclear(res, free), false);
	ft_lstadd_back(res, new);
	return (true);
}

bool	remove_quotes_list(t_list **res_old)
{
	t_list	*head;
	t_list	*res;
	t_list	*new;
	t_list	*tmp;

	res = NULL;
	head = *res_old;
	tmp = *res_old;
	while (tmp)
	{
		new = remove_quotes(tmp->content);
		if (new == NULL)
			return (ft_lstclear(&res, free), false);
		ft_lstadd_back(&res, new);
		tmp = tmp->next;
	}
	ft_lstclear(&head, free);
	*res_old = res;
	return (true);
}
