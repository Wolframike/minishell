/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:11:32 by knishiok          #+#    #+#             */
/*   Updated: 2023/12/10 23:31:15 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*parse_pipeline(t_token **token, t_state *data)
{
	t_ast_node	*res;
	t_ast_node	*r_node;

	if (consume_token(token, TK_LPAREN))
		res = parse_subshell(token, data);
	else
		res = parse_simple_command(token, data);
	while (token != NULL && (res != NULL && res->type != TK_EOL)
		&& consume_token(token, TK_PIPE))
	{
		if (consume_token(token, TK_LPAREN))
			r_node = parse_subshell(token, data);
		else
			r_node = parse_simple_command(token, data);
		if (r_node == NULL)
			return (destroy_ast_node(res), NULL);
		res = new_ast_node(AST_PIPE, res, r_node);
		if (res == NULL)
			return (destroy_ast_node(r_node), NULL);
	}
	return (res);
}
