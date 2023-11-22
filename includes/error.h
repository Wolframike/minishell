/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:08:20 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/20 14:47:55 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "type.h"

void	set_allocation_error(t_state *data, t_token *token);
void	set_syntax_error(t_state *data);

#endif
