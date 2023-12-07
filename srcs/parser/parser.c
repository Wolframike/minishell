/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:11:42 by knishiok          #+#    #+#             */
/*   Updated: 2023/12/07 23:02:32 by knishiok         ###   ########.fr       */
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
	if (res == NULL && !data->interrupted)
		ft_putendl_fd("minishell: syntax error", STDERR_FILENO);
	destroy_token(&(data->token));
	if (token != NULL)
		return (destroy_ast_node(res), NULL);
	return (res);
}
