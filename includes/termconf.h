/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termconf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 21:28:30 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/27 22:14:53 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCONF_H
# define TERMCONF_H

# include "type.h"
# include "error.h"
# include <term.h>
# include <termios.h>
# include <curses.h>

void	set_term_config(t_state *data, int mode);
#endif
