/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termconf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 21:28:30 by knishiok          #+#    #+#             */
/*   Updated: 2023/12/10 23:19:09 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCONF_H
# define TERMCONF_H

# include "type.h"
# include "error.h"
# include <term.h>
# include <termios.h>

# define PROMPT "\033[1;34mminishell\033[0m\033[1;33m|\033[0m\033[1;32m➜\033[0m  "

typedef struct s_state	t_state;

void	set_term_config(t_state *data);
#endif
