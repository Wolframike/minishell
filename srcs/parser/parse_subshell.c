/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 23:38:38 by knishiok          #+#    #+#             */
/*   Updated: 2023/12/08 18:46:53 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*parse_subshell(t_token **token, t_state *data)
{
	t_ast_node	*res;
	t_ast_node	*lnode;
	t_list		*redir;

	lnode = parse_and_or(token, data);
	if (lnode == NULL)
		return (NULL);
	res = new_ast_node(AST_SUBSHELL, lnode, NULL);
	if (res == NULL)
		return (destroy_ast_node(lnode), NULL);
	if (!consume_token(token, TK_RPAREN))
		return (destroy_ast_node(res), NULL);
	if (!is_redir(*token))
		return (res);
	redir = parse_io_files(token, data);
	if (redir == NULL)
		return (destroy_ast_node(res), NULL);
	res->redir = redir;
	return (res);
}
