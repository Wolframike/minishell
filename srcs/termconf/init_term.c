/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 21:22:27 by knishiok          #+#    #+#             */
/*   Updated: 2023/12/06 15:45:48 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termconf.h"

void	set_term_config(t_state *data, int mode)
{
	static int	default_lflag;
	static int	default_vtime;

	if (mode == 0)
	{
		if (tcgetattr(STDIN_FILENO, &(data->termconf)) == -1)
		{
			operation_failed("tcgetattr");
			exit(EXIT_KO);
		}
		default_lflag = data->termconf.c_lflag;
		default_vtime = data->termconf.c_cc[VTIME];
		data->termconf.c_lflag &= ~ICANON;
		data->termconf.c_cc[VTIME] = 1;
	}
	else if (mode == 1)
	{
		data->termconf.c_lflag = default_lflag;
		data->termconf.c_cc[VTIME] = default_vtime;
		if (tcsetattr(STDIN_FILENO, TCSANOW, &(data->termconf)) == -1)
		{
			operation_failed("tcsetattr");
			exit(EXIT_KO);
		}
	}
}
