/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 21:04:03 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/29 15:28:25 by knishiok         ###   ########.fr       */
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
char	*expand_variable(char *line, t_env *env);
bool	expand_command_list(t_list **command, t_env *env);

#endif
