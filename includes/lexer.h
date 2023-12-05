/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:11:41 by knishiok          #+#    #+#             */
/*   Updated: 2023/12/01 19:07:16 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "type.h"
# include "error.h"

typedef struct s_token	t_token;
typedef struct s_state	t_state;

void	destroy_token(t_token **token);
bool	is_space(const char c);
void	skip_spaces(const char **line);
bool	is_metacharacter(const char c);
bool	corresponds(const char *line, const char *metastr);

void	tokenize(t_state *data, const char *line);

void	print_tokens(t_token *token);

#endif
