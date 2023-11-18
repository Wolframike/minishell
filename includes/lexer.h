/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:11:41 by knishiok          #+#    #+#             */
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

void	tokenize(t_data *data, char *line);

#endif
