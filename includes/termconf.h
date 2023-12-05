/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termconf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 21:28:30 by knishiok          #+#    #+#             */
/*   Updated: 2023/12/01 19:06:51 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCONF_H
# define TERMCONF_H

# include "type.h"
# include "error.h"
# include <term.h>
# include <termios.h>
# include <curses.h>

typedef struct s_state	t_state;

void	set_term_config(t_state *data, int mode);
#endif
