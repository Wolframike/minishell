/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:34:44 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/21 03:01:55 by misargsy         ###   ########.fr       */
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

//exec_pipeline.c
t_exit_code	exec_pipeline(t_ast_node *root);

//set_redir.c
void		set_redir(t_ast_node *node, int *fd[2]);

//error.c
void		command_not_found(char *command);
void		permission_denied(char *filename);
void		operation_failed(char *operation);

#endif