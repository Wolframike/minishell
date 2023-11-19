/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:57:35 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/19 21:33:23 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_H
# define TYPE_H

# include "libft.h"
# include <stdbool.h>

typedef enum e_token_type
{
	TK_AND,
	TK_OR,
	TK_IN,
	TK_OUT,
	TK_HEREDOC,
	TK_APPEND,
	TK_PIPE,
	TK_WORD,
	TK_EOL,
}	t_token_type;

typedef struct s_list
{
	struct s_list	*prev;
	struct s_list	*next;
	void			*value;
}	t_list;

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
	int		status;
	bool	sys_error;
}	t_data;

enum e_exit_code
{
	EIXT_BUILTIN = 2,
	EXIT_EXEC = 126,
	EXIT_NOENT,
	EXIT_INVAL,
	EXIT_SEGV = 255
};

#endif
