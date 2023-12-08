/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:10:39 by knishiok          #+#    #+#             */
/*   Updated: 2023/12/07 23:53:10 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "type.h"
# include "lexer.h"

typedef struct s_redir		t_redir;
typedef struct s_ast_node	t_ast_node;
typedef struct s_state		t_state;
typedef struct s_token		t_token;
typedef enum e_ast_type		t_ast_type;
typedef enum e_redir_type	t_redir_type;
typedef enum e_token_type	t_token_type;

void		destroy_redir(t_redir *redir);
void		destroy_ast_node(t_ast_node *node);
bool		is_redir(t_token *token);
// void		eat_token(t_token **token);
bool		consume_token(t_token **token, t_token_type type);

bool		add_command(t_ast_node *node, char *command);
bool		add_redir(t_ast_node *node, t_list *redir);
t_ast_node	*new_ast_node(t_ast_type type,
				t_ast_node *left, t_ast_node *right);
t_redir		*new_redir(t_redir_type type, char *filename);

t_ast_node	*parse_and_or(t_token **token, t_state *data);
t_ast_node	*parse_subshell(t_token **token, t_state *data);
t_ast_node	*parse_pipeline(t_token **token, t_state *data);
t_ast_node	*parse_simple_command(t_token **token, t_state *data);
bool		parse_cmd_suffix(t_token **token, t_ast_node *node, t_state *data);
t_ast_node	*parse_word_cmd_suffix(t_token **token, t_state *data);
t_redir		*parse_heredoc(t_token **token, t_state *data);
t_list		*parse_io_files(t_token **token, t_state *data);
char		*parse_word(t_token **token);
t_list		*parse_io_file(t_token **token, t_state *data);

void		print_command_list(t_list *list);
void		print_node(t_ast_node *node);
void		print_redir_list(t_list *list);

#endif
