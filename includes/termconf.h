/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termconf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 21:28:30 by knishiok          #+#    #+#             */
/*   Updated: 2023/12/07 19:02:25 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCONF_H
# define TERMCONF_H

# include "type.h"
# include "error.h"
# include <term.h>
# include <termios.h>
# include <curses.h>

# define PROMPT "\033[1;34mminishell\033[0m\033[1;33m|\033[0m\033[1;32m➜\033[0m  "

typedef struct s_state	t_state;

void	set_term_config(t_state *data);
#endif
