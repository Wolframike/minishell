/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 21:22:27 by knishiok          #+#    #+#             */
/*   Updated: 2023/12/11 06:44:42 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termconf.h"

void	set_term_config(t_state *data)
{
	struct termios	termconf;

	if (tcgetattr(STDIN_FILENO, &termconf) == -1)
	{
		operation_failed("tcsetattr");
		if (!set_env(&data->env, "?", "1"))
			operation_failed("malloc");
		return ;
	}
	termconf.c_lflag |= (PENDIN | ICANON | ECHO);
	termconf.c_lflag &= ~NOFLSH;
	termconf.c_iflag |= ICRNL;
	termconf.c_oflag |= ONLCR;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &termconf) == -1)
	{
		operation_failed("tcsetattr");
		if (!set_env(&data->env, "?", "1"))
			operation_failed("malloc");
		return ;
	}
}
