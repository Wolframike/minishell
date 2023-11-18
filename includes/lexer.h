/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:11:41 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/18 18:22:34 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum e_token_type
{
	TK_AND,
	TK_OR,
	TK_IN,
	TK_OUT,
	TK_HEREDOC,
	TK_APPEND,
	TK_WORD,
	TK_PIPE,
	TK_EOF,
}	t_token_type;

typedef struct s_token
{
	char			*word;
	t_token_type	type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_data
{
	t_token	*token;
}	t_data;

#endif
