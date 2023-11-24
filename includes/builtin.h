/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:14:09 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/24 23:24:17 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "lexer.h"
# include "libft.h"
# include "type.h"
# include <stdbool.h>
# include <sys/errno.h>
# include <string.h>

extern char	**environ;

int		bi_echo(t_list *args);

bool	move_to_envvar(char *varname);
bool	move_to_path(char *path);
int		bi_cd(t_list *args);


int		bi_pwd(void);
int		bi_export(t_list *args);
int		bi_unset(t_list *args);
int		bi_env(void);
int		bi_exit(t_list *args, bool parent);

void	too_many_arguments(char *command);

#endif