/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:34:44 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/08 20:59:25 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "type.h"
# include "builtin.h"
# include "ast.h"
# include "utils.h"
# include "env.h"
# include "sig.h"
# include "expand.h"
# include "error.h"
# include <fcntl.h>

# define PERMS 0644
# define ENOCMD -1

typedef struct s_exec		t_exec;
typedef struct s_env		t_env;
typedef struct s_ast_node	t_ast_node;
typedef struct s_token		t_token;
typedef enum e_exit_code	t_exit_code;

//ft_execvp.c
int			ft_execvp(const char *file, char *const argv[], char *const *envp);
char		**t_list_to_array(const char *command, t_list *lst);

//exec_single_pipe.c
bool		exec_pipeline_list(t_list *head, t_exec *config);

//exec_pipeline.c
void		exec_pipeline(t_ast_node *root, t_exec *config);

//set_redir.c
bool		set_redir(t_list *redirects, t_env *env);
void		only_redir(t_list *redirects, t_env *env, t_exec *config);

//error.c
void		command_not_found(const char *command);
void		permission_denied(const char *filename);
void		operation_failed(const char *operation);
t_exit_code	execvp_failed(const char *command);

//execute.c
void		exec_subshell(t_ast_node *root, t_exec *config);
void		execute(t_ast_node *root, t_exec *config);

//exec_util.c
void		exec_non_bi_in_child_process(const char *command, t_list *args,
				t_exec *config);
bool		set_expanded_args(t_ast_node *root, t_exec *config);
t_exit_code	single_fork_destructor(pid_t pid, t_exec *config);
t_exit_code	pipeline_forks_destructor(t_exec *config);

#endif
