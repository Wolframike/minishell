/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:57:35 by knishiok          #+#    #+#             */
/*   Updated: 2023/12/01 18:50:09 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_H
# define TYPE_H

# include "libft.h"
# include "env.h"
# include <term.h>
# include <termios.h>
# include <stdbool.h>

typedef struct s_env	t_env;

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

typedef struct s_token
{
	char			*word;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_state
{
	struct termios	*termconf;
	t_token			*token;
	t_env			*env;
	int				status;
	int				heredoc_count;
	bool			sys_error;
}	t_state;

typedef enum e_exit_code
{
	EXIT_OK = EXIT_SUCCESS,
	EXIT_KO = EXIT_FAILURE,
	EXIT_BUILTIN = 2,
	EXIT_EXEC = 126,
	EXIT_NOENT,
	EXIT_INVAL,
	EXIT_SEGV = 255
}	t_exit_code;

#endif
