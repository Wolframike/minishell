/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:41:20 by knishiok          #+#    #+#             */
/*   Updated: 2023/12/11 04:15:06 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	destroy_token(t_token **token)
{
	if (*token == NULL)
		return ;
	free((*token)->word);
	(*token)->word = NULL;
	destroy_token(&(*token)->next);
	free(*token);
	*token = NULL;
}

bool	has_valid_parentheses(const char *line)
{
	int		i;
	int		cnt;
	char	quote;

	quote = '\0';
	i = -1;
	cnt = 0;
	while (line[++i])
	{
		if (ft_strchr("\'\"", line[i]))
		{
			if (quote == '\0')
				quote = line[i];
			else if (quote == line[i])
				quote = '\0';
		}
		if (line[i] == '(' && quote == '\0')
			cnt++;
		if (line[i] == ')' && quote == '\0')
			cnt--;
		if (cnt < 0)
			return (false);
	}
	return (cnt == 0);
}

void	skip_spaces(const char **line)
{
	while (**line && ft_strchr(" \n\t", **line))
		(*line)++;
}

bool	is_metacharacter(const char c)
{
	return (c == '|' || c == '&' || c == '<'
		|| c == '>' || c == '(' || c == ')');
}

// Checks if the given string 'line' corresponds to the specified 'metastr'
bool	corresponds(const char *line, const char *metastr)
{
	return (ft_strncmp(line, metastr, ft_strlen(metastr)) == 0);
}
