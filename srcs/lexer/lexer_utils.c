/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:41:20 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/21 05:01:56 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

bool	is_space(const char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

void	skip_spaces(const char **line)
{
	while (is_space(**line))
		(*line)++;
}

bool	is_metacharacter(const char c)
{
	return (c == '|' || c == '&' || c == '<' || c == '>');
}

// Checks if the given string 'line' corresponds to the specified 'metastr'
bool	corresponds(const char *line, const char *metastr)
{
	return (ft_strncmp(line, metastr, ft_strlen(metastr)) == 0);
}
