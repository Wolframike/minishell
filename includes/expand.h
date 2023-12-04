/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 21:04:03 by knishiok          #+#    #+#             */
/*   Updated: 2023/12/02 21:58:21 by knishiok         ###   ########.fr       */
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

bool	skip_line(char **line, char *res_old, char **res);
t_list	*dup_string_to_list(char *string);
char	*expand_variable_heredoc(char *line, t_env *env);
bool	expand_variable(char *line, t_env *env, char **expanded);
bool	expand_command_list(t_list *command, t_env *env, t_list **head);

#endif
