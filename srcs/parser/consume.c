/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consume.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:14:12 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/25 15:34:17 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	destroy_token(t_token **token)
{
	if (*token == NULL)
		return ;
	free((*token)->word);
	(*token)->word = NULL;
	free(*token);
	*token = NULL;
}

void	eat_token(t_token **token)
{
	t_token	*del_token;

	del_token = *token;
	*token = (*token)->next;
	destroy_token(&del_token);
}

bool	consume_token(t_token **token, t_token_type type)
{
	t_token	*del_token;

	if (token == NULL || *token == NULL)
		return (false);
	if ((*token)->type == type)
	{
		del_token = *token;
		*token = (*token)->next;
		destroy_token(&del_token);
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
