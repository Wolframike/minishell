/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:10:39 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/22 16:03:18 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "lexer.h"
# include "type.h"
// debug
# include <stdio.h>

typedef enum e_ast_type
{
	AST_CMD,
	AST_AND,
	AST_OR,
	AST_PIPE,
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

void		destroy_token(t_token **token);
void		destroy_redir(t_redir *redir);
void		destroy_ast_node(t_ast_node *node);
bool		is_redir(t_token *token);
void		eat_token(t_token **token);
bool		consume_token(t_token **token, t_token_type type);

bool		add_command(t_ast_node *node, char *command);
bool		add_redir(t_ast_node *node, t_list *redir);
t_ast_node	*new_ast_node(t_ast_type type,
				t_ast_node *left, t_ast_node *right);
t_redir		*new_redir(t_redir_type type, char *filename);

t_ast_node	*parse_and_or(t_token **token);
t_ast_node	*parse_pipeline(t_token **token);
t_ast_node	*parse_simple_command(t_token **token);
bool		parse_cmd_suffix(t_token **token, t_ast_node *node);
t_ast_node	*parse_word_cmd_suffix(t_token **token);
t_list		*parse_io_file(t_token **token);
t_list		*parse_io_files(t_token **token);
char		*parse_word(t_token **token);

void		print_command_list(t_list *list);
void		print_node(t_ast_node *node);
void		print_redir_list(t_list *list);
#endif
