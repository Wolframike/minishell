/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 21:04:03 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/27 19:17:23 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "type.h"
# include "ast.h"
# include "env.h"
# include "error.h"
# include <stdbool.h>

char	*expand_variable(char *line, t_env *env);
bool	expand_command_list(t_list **command, t_env *env);

#endif
