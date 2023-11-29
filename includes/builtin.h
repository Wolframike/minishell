/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:14:09 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/28 19:08:01 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "lexer.h"
# include "libft.h"
# include "type.h"
# include "error.h"
# include "execute.h"
# include "expand.h"
# include "termconf.h"
# include <stdbool.h>
# include <sys/errno.h>
# include <string.h>

typedef struct s_exec	t_exec;

int		bi_echo(t_list *args, t_exec *config);

bool	move_to_envvar(t_exec *config, char *varname);
bool	move_to_path(t_exec *config, char *path);
int		bi_cd(t_list *args, t_exec *config);

int		bi_pwd(void);
int		bi_export(t_list *args, t_exec *config);
int		bi_unset(t_list *args, t_exec *config);
int		bi_env(t_exec *config);
int		bi_exit(t_list *args, bool parent, t_exec *config);

bool	is_valid_identifier(char *str);

#endif
