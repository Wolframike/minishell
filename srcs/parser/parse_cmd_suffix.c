/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_suffix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:11:14 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/20 18:06:42 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*parse_word_cmd_suffix(t_token *token)
{
	t_ast_node	*res;
	char		*command;

	res = new_ast_node(AST_CMD);
	command = parse_word(token);
	if (!add_command(res, command))
	{
		destroy_node(res);
		free(command);
		return (NULL);
	}
	
}