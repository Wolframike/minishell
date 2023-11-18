/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:56:10 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/18 19:30:15 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

void	set_allocation_error(t_data *data, t_token *token)
{
	data->sys_error = true;
	data->token = token;
}

void	set_syntax_error(t_data *data)
{
	data->status = 1;
	data->sys_error = true;
	ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
}
