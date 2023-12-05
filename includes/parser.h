/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:10:59 by knishiok          #+#    #+#             */
/*   Updated: 2023/12/01 19:06:43 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "type.h"
# include "ast.h"
# include "sig.h"

typedef struct s_state		t_state;
typedef struct s_ast_node	t_ast_node;

t_ast_node	*parse(t_state *data, char *line);

#endif
