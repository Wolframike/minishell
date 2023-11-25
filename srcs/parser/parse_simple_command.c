/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:11:37 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/25 19:29:54 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*parse_simple_command(t_token **token)
{
	t_list		*redir;
	t_ast_node	*res;

	redir = NULL;
	if (is_redir(*token))
	{
		redir = parse_io_files(token);
		if (redir == NULL)
			return (NULL);
	}
	else if (!(*token && (*token)->type == TK_WORD))
		return (NULL);
	if (*token && (*token)->type == TK_WORD)
	{
		res = parse_word_cmd_suffix(token);
		return (res);
	}
	res = new_ast_node(AST_CMD, NULL, NULL);
	add_redir(res, redir);
	return (res);
}
