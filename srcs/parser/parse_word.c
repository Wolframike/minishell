/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:00:45 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/27 19:32:07 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*parse_word(t_token **token)
{
	char	*res;

	if (*token == NULL || (*token)->word == NULL
		|| (*token)->type != TK_WORD)
		return (NULL);
	res = ft_strdup((*token)->word);
	if (res == NULL)
		return (NULL);
	consume_token(token, TK_WORD);
	return (res);
}
