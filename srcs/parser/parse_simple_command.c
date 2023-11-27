/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:11:37 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/27 19:26:12 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*parse_simple_command(t_token **token, t_state *data)
{
	t_list		*redir;
	t_ast_node	*res;

	redir = NULL;
	if (is_redir(*token))
	{
		redir = parse_io_files(token, data);
		if (redir == NULL)
			return (NULL);
	}
	else if (!(*token && (*token)->type == TK_WORD))
		return (NULL);
	if (*token && (*token)->type == TK_WORD)
	{
		res = parse_word_cmd_suffix(token, data);
		return (res);
	}
	res = new_ast_node(AST_CMD, NULL, NULL);
	add_redir(res, redir);
	return (res);
}
