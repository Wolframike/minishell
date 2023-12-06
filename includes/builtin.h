/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:14:09 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/06 18:51:38 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "type.h"
# include "lexer.h"
# include "libft.h"
# include "type.h"
# include "error.h"
# include "execute.h"
# include "expand.h"
# include "utils.h"
# include "termconf.h"
# include <stdbool.h>
# include <sys/errno.h>
# include <string.h>

typedef struct s_exec	t_exec;
typedef struct s_env	t_env;

int		bi_echo(t_list *args, t_exec *config);

bool	move_to_path(const char *target_path, t_exec *config);
int		bi_cd(t_list *args, t_exec *config);

int		bi_pwd(t_exec *config);

bool	print_declare(t_env *env);
int		bi_export(t_list *args, t_exec *config);

int		bi_unset(t_list *args, t_exec *config);
int		bi_env(t_exec *config);
int		bi_exit(t_list *args, bool parent, t_exec *config);

bool	is_valid_identifier(char *str);

#endif
