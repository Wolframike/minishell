/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:11:32 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/21 06:05:25 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*parse_pipeline(t_token **token)
{
	t_ast_node	*res;
	t_ast_node	*r_node;

	res = parse_simple_command(token);
	while (token != NULL && (res != NULL && res->type != TK_EOL)
		&& consume_token(token, TK_PIPE))
	{
		r_node = parse_simple_command(token);
		if (r_node == NULL)
		{
			destroy_ast_node(res);
			return (NULL);
		}
		res = new_ast_node(AST_PIPE, res, r_node);
		if (res == NULL)
		{
			destroy_ast_node(r_node);
			return (NULL);
		}
	}
	return (res);
}
