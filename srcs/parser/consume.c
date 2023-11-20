/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consume.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:14:12 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/20 15:48:48 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	destory_token(t_token *token)
{
	free(token->next);
	free(token->prev);
	free(token->word);
}

bool	consume_token(t_token **token, t_token_type type)
{
	t_token	*del_token;

	if ((*token)->type == type)
	{
		del_token = *token;
		*token = (*token)->next;
		destory_token(del_token);
		return (true);
	}
	return (false);
}

bool	is_redirect(t_token *token)
{
	return ((token->type == TK_IN)
		|| (token->type == TK_OUT)
		|| (token->type == TK_APPEND)
		|| (token->type == TK_HEREDOC));
}
