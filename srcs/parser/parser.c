/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:11:42 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/27 19:24:34 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*parse(t_state *data, char *line)
{
	t_token		*token;
	t_ast_node	*res;

	tokenize(data, line);
	if (data->token == NULL)
		return (NULL);
	token = data->token;
	res = parse_and_or(&token, data);
	destroy_token(&(data->token));
	if (token != NULL)
	{
		destroy_ast_node(res);
		return (NULL);
	}
	return (res);
}
