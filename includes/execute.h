/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:34:44 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/22 20:32:14 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "builtin.h"
# include "ast.h"
# include "type.h"
# include <fcntl.h>

# define PERMS 0644

// typedef struct s_execute
// {
// 	e_exit_code		exit_code;
// }	t_execute;

extern char	**environ;

//ft_execvp.c
int			ft_execvp(const char *file, char *const argv[]);
char		**t_list_to_char_arr(const char *command, t_list *lst);
void		free2darr(char **arr);

//exec_pipeline.c
t_exit_code	exec_pipeline(t_ast_node *root);

//set_redir.c
bool		set_redir(t_list *redirects, int (*fd)[2]);

//error.c
void		command_not_found(const char *command);
void		permission_denied(const char *filename);
void		operation_failed(const char *operation);
t_exit_code	execvp_failed(const char *command);

//execute.c
t_exit_code	execute(t_ast_node *root);

#endif