/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 21:04:03 by knishiok          #+#    #+#             */
/*   Updated: 2023/12/01 16:31:59 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "type.h"
# include "ast.h"
# include "env.h"
# include "error.h"
# include <stdbool.h>
# include <dirent.h>

bool	matched(char *filename, char *pattern, bool *flg);
t_list	*expand_wildcard(t_list **input);

char	*expand_variable_heredoc(char *line, t_env *env);
bool	expand_variable(char *line, t_env *env, char **expanded);
bool	expand_command_list(t_list *command, t_env *env, t_list **head);

#endif
