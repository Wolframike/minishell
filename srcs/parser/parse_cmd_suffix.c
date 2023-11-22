/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_suffix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:11:14 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/21 04:28:49 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	parse_redirects_helper(t_token **token, t_ast_node *node)
{
	t_list	*redir;

	redir = parse_io_file(token);
	if (!add_redir(node, redir))
	{
		ft_lstclear(&redir, (void (*)(void *))destroy_redir);
		return (false);
	}
	return (true);
}

bool	parse_cmd_suffix(t_token **token, t_ast_node *node)
{
	char	*word;

	while (*token && ((*token)->type == TK_WORD || is_redir(*token)))
	{
		if ((*token)->type == TK_WORD)
		{
			word = parse_word(token);
			if (!add_command(node, word))
			{
				free(word);
				return (false);
			}
		}
		else
		{
			if (!parse_redirects_helper(token, node))
				return (false);
		}
	}
	return (true);
}

t_ast_node	*parse_word_cmd_suffix(t_token **token)
{
	t_ast_node	*res;
	char		*command;

	res = new_ast_node(AST_CMD, NULL, NULL);
	command = parse_word(token);
	if (!add_command(res, command))
	{
		destroy_ast_node(res);
		free(command);
		return (NULL);
	}
	if (*token != NULL && (((*token)->type == TK_WORD) || is_redir(*token)))
	{
		if (!parse_cmd_suffix(token, res))
		{
			free(command);
			return (NULL);
		}
	}
	return (res);
}
