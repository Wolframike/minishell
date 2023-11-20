/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:10:47 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/20 14:47:55 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "type.h"
# include "error.h"

bool	is_space(char c);
void	skip_spaces(char **line);
bool	is_metacharacter(char c);
bool	corresponds(char *line, const char *metastr);

void	tokenize(t_state *data, const char *line);

#endif
