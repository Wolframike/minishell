/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consume.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:14:12 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/26 18:10:43 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	consume_token(t_token **token, t_token_type type)
{
	if (token == NULL || *token == NULL)
		return (false);
	if ((*token)->type == type)
	{
		*token = (*token)->next;
		return (true);
	}
	return (false);
}

bool	is_redir(t_token *token)
{
	if (token == NULL)
		return (false);
	return ((token->type == TK_IN)
		|| (token->type == TK_OUT)
		|| (token->type == TK_APPEND)
		|| (token->type == TK_HEREDOC));
}
