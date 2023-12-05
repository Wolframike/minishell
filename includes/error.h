/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 19:08:20 by knishiok          #+#    #+#             */
/*   Updated: 2023/12/05 10:10:02 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "type.h"
# include "execute.h"
# include <sys/errno.h>
# include <string.h>

typedef struct s_token		t_token;
typedef struct s_state		t_state;
typedef enum e_exit_code	t_exit_code;

//general_errors.c
void		no_such_file_or_directory(const char *command, const char *path);
void		command_not_found(const char *command);
void		permission_denied(const char *filename);
void		operation_failed(const char *operation);

//lexer_errors.c
void		set_allocation_error(t_state *data, t_token *token);
void		set_syntax_error(t_state *data);

//bi_errors.c
void		too_many_arguments(const char *command);
void		file_name_too_long(const char *command, const char *path);
void		not_a_valid_identifier(const char *command, const char *arg);
void		error_retrieving_cd(const char *operation);

//exec_errors.c
t_exit_code	execvp_failed(const char *command);
void		ambiguous_redirect(const char *filename);

#endif
