/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 21:04:03 by knishiok          #+#    #+#             */
/*   Updated: 2023/12/07 18:10:46 by misargsy         ###   ########.fr       */
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

typedef struct s_env	t_env;

void	destroy_table(bool **table, int height);
int		count_patlen(char *line);
bool	*expand_or_not(char *line);

bool	matched(char *filename, char *pattern, bool *flg);
t_list	*expand_wildcard(t_list **input);

t_list	*remove_quotes(char *line);
bool	handle_quote(t_list **res, char **line);
bool	remove_quotes_list(t_list **res_old);

t_list	*dup_string_to_list(char *string);
bool	get_filenames(t_list **res);

bool	skip_line(char **line, char *res_old, char **res);

char	*expand_variable_heredoc(char *line, t_env *env);
bool	expand_variable_export(char *line, t_env *env, char **expanded);
bool	expand_variable(char *line, t_env *env, char **expanded);
bool	expand_variable_to_list(char *line, t_env *env, t_list **res);
bool	expand_command_list(t_list *command, t_env *env, t_list **head);

#endif
