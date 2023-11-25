/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:56:10 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/25 15:17:02 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

void	set_allocation_error(t_state *data, t_token *token)
{
	data->sys_error = true;
	data->token = token;
}

void	set_syntax_error(t_state *data)
{
	data->status = 1;
	data->sys_error = true;
	ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
}
