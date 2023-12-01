/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_or.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:11:09 by knishiok          #+#    #+#             */
/*   Updated: 2023/12/01 21:02:03 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_ast_node	*parse_and(t_token **token, t_ast_node **node,
									t_state *data)
{
	t_ast_node	*res;
	t_ast_node	*r_node;

	r_node = parse_pipeline(token, data);
	if (r_node == NULL)
	{
		destroy_ast_node(*node);
		return (NULL);
	}
	res = new_ast_node(AST_AND, *node, r_node);
	if (res == NULL)
	{
		destroy_ast_node(r_node);
		destroy_ast_node(*node);
	}
	return (res);
}

static t_ast_node	*parse_or(t_token **token, t_ast_node **node, t_state *data)
{
	t_ast_node	*res;
	t_ast_node	*r_node;

	r_node = parse_pipeline(token, data);
	if (r_node == NULL)
	{
		destroy_ast_node(*node);
		return (NULL);
	}
	res = new_ast_node(AST_OR, *node, r_node);
	if (res == NULL)
	{
		destroy_ast_node(r_node);
		destroy_ast_node(*node);
	}
	return (res);
}

t_ast_node	*parse_and_or(t_token **token, t_state *data)
{
	t_ast_node	*res;

	if ((*token)->type == TK_AND || (*token)->type == TK_OR)
		return (NULL);
	res = parse_pipeline(token, data);
	while (res != NULL && res->type != TK_EOL)
	{
		if (consume_token(token, TK_AND))
		{
			res = parse_and(token, &res, data);
			if (res == NULL)
				return (NULL);
		}
		else if (consume_token(token, TK_OR))
		{
			res = parse_or(token, &res, data);
			if (res == NULL)
				return (NULL);
		}
		else
			break ;
	}
	return (res);
}
