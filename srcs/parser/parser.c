/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:11:42 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/20 15:40:22 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*parse(t_state *data, char *line)
{
	t_token		*token;
	t_ast_node	*res;

	token = tokenize(data, line);
	if (token == NULL)
		return (NULL);
	res = parse_and_or(token);
	if (token->type != TK_EOL)
	{
		destroy_token(token);
		destory_node(res);
		return (NULL);
	}
	destroy_token(token);
	return (res);
}
