/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_or.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:11:09 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/20 15:29:17 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_ast_node	*parse_and(t_token *token, t_ast_node **node)
{
	t_ast_node	*res;
	t_ast_node	*r_node;

	r_node = parse_pipeline(token);
	if (r_node == NULL)
	{
		destroy_node(*node);
		return (NULL);
	}
	res = new_ast_node(AST_AND, *node, r_node);
	if (res == NULL)
	{
		destroy_node(r_node);
		destroy_node(*node);
	}
	return (res);
}

static t_ast_node	*parse_or(t_token *token, t_ast_node **node)
{
	t_ast_node	*res;
	t_ast_node	*r_node;

	r_node = parse_pipeline(token);
	if (r_node == NULL)
	{
		destroy_node(*node);
		return (NULL);
	}
	res = new_ast_node(AST_OR, *node, r_node);
	if (res == NULL)
	{
		destroy_node(r_node);
		destroy_node(*node);
	}
	return (res);
}

t_ast_node	*parse_and_or(t_token *token)
{
	t_ast_node	*res;

	// syntax error
	if (token->type == TK_AND || token->type == TK_OR)
		return (NULL);
	res = parse_pipeline(token);
	while (res != NULL && res->type != TK_EOL)
	{
		if (consume_token(token, TK_AND))
		{
			res = parse_and(token, &res);
			if (res == NULL)
				return (NULL);
		}
		else if (consume_token(token, TK_AND))
		{
			res = parse_or(token, &res);
			if (res == NULL)
				return (NULL);
		}
		// ここに該当したらsyntax error
		else
			break;
	}
	return (NULL);
}
