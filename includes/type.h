/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:57:35 by knishiok          #+#    #+#             */
/*   Updated: 2023/12/07 23:51:44 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_H
# define TYPE_H

# include "libft.h"
# include "env.h"
# include <term.h>
# include <termios.h>
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
	TK_LPAREN,
	TK_RPAREN,
}	t_token_type;

typedef struct s_token
{
	char			*word;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_state
{
	struct termios	termconf;
	t_token			*token;
	t_env			*env;
	bool			interrupted;
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

typedef enum e_ast_type
{
	AST_CMD,
	AST_AND,
	AST_OR,
	AST_PIPE,
	AST_SUBSHELL,
}	t_ast_type;

typedef struct s_ast_node
{
	t_ast_type			type;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	t_list				*redir;
	t_list				*command;
}	t_ast_node;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*filename;
}	t_redir;

typedef struct s_exec
{
	t_env			*env;
	t_list			*expanded;
	t_exit_code		exit_code;
	char			*cwd;
	int				fork_count;
}	t_exec;

#endif
