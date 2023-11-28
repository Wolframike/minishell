/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:34:44 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/28 17:08:29 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "builtin.h"
# include "ast.h"
# include "type.h"
# include "utils.h"
# include "env.h"
# include "sig.h"
# include "expand.h"
# include <fcntl.h>

# define PERMS 0644

typedef struct s_exec
{
	t_env			*env;
	t_exit_code		exit_code;
	int				fork_count;
}	t_exec;

//ft_execvp.c
int			ft_execvp(const char *file, char *const argv[], char *const *envp);
char		**t_list_to_array(const char *command, t_list *lst);

//exec_pipeline.c
t_exit_code	exec_pipeline(t_ast_node *root, t_exec *config);

//set_redir.c
bool		set_redir(t_list *redirects, int (*fd)[2]);

//error.c
void		command_not_found(const char *command);
void		permission_denied(const char *filename);
void		operation_failed(const char *operation);
t_exit_code	execvp_failed(const char *command);

//execute.c
t_exit_code	execute(t_ast_node *root, t_exec *config);

//exec_util.c
void		exec_in_pipeline(t_ast_node *root, t_exec *config);
t_exit_code	exec_non_bi(const char *command, t_list *args, t_exec *config);

#endif
