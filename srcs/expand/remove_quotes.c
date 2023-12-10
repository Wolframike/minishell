/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 21:08:48 by knishiok          #+#    #+#             */
/*   Updated: 2023/12/11 01:55:04 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

bool	skip_line(char **line, char **res)
{
	int		i;
	int		src_len;
	char	*res_old;

	if (!strdup_case_null(&res_old, *res))
		return (operation_failed("malloc"), false);
	src_len = ft_strlen(res_old);
	free(*res);
	*res = ft_calloc(src_len + 2, sizeof(char));
	if (*res == NULL)
		return (free(res_old), operation_failed("malloc"), false);
	i = -1;
	while (++i < src_len)
		(*res)[i] = res_old[i];
	(*res)[src_len] = **line;
	free(res_old);
	(*line)++;
	return (true);
}

static bool	update_quote(char **line, char *quote)
{
	if (*quote == '\0')
	{
		*quote = **line;
		(*line)++;
		return (true);
	}
	else if (*quote == **line)
	{
		*quote = '\0';
		(*line)++;
		return (true);
	}
	return (false);
}

t_list	*remove_quotes(char *line)
{
	t_list	*res;
	char	*res_str;
	char	quote;

	res_str = ft_strdup("");
	if (res_str == NULL)
		return (NULL);
	quote = '\0';
	while (*line)
	{
		if ((*line == '\'' || *line == '\"') && update_quote(&line, &quote))
			continue ;
		if (!skip_line(&line, &res_str))
			return (free(res_str), NULL);
	}
	res = ft_lstnew(res_str);
	if (res == NULL)
		return (free(res_str), NULL);
	return (res);
}

bool	handle_quote(t_list **res, char **line)
{
	char	quote;
	char	*word_start;
	char	*chunk;
	t_list	*new;

	word_start = *line;
	quote = '\0';
	while (**line)
	{
		if (ft_strchr(" \n\t", **line) && quote == '\0')
			break ;
		else if (ft_strchr("\'\"", **line) && update_quote(line, &quote))
			continue ;
		(*line)++;
	}
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
