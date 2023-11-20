/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:11:37 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/20 17:40:34 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*parse_simple_command(t_token *token)
{
	t_list		*redir;
	t_ast_node	*res;

	redir = ft_calloc(1, sizeof(t_redir));
	if (is_redirect(token))
	{
		redir = parse_io_files(token);
		if (redir == NULL)
			return (NULL);
	}
	if (token->type == TK_WORD)
	{
		res = parse_word_cmd_suffix(token);
		res->redir = redir;
		return (res);
	}
	return (NULL);
}