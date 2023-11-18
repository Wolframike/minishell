/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:14:09 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/18 20:03:23 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "lexer.h"
# include "libft.h"
# include "type.h"
# include <stdbool.h>

int	bi_echo(t_token *token);
int	bi_exit(t_token *token, bool parent);

#endif