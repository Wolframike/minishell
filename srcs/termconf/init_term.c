/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 21:22:27 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/27 22:37:21 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termconf.h"

// static void	set_read_mode(t_state *data)
// {
// 	tcsetattr(STDIN_FILENO, TCSANOW, data->termconf);
// }

void	set_term_config(t_state *data, int mode)
{
	static struct termios	default_setting;

	if (mode == 0)
	{
		data->termconf = ft_calloc(1, sizeof(struct termios));
		if (data->termconf == NULL)
			return (operation_failed("malloc"));
		tgetent(NULL, getenv("TERM"));
		tcgetattr(STDIN_FILENO, &default_setting);
		ft_memcpy(data->termconf, &default_setting, sizeof(struct termios));
		data->termconf->c_iflag &= ~(IXON);
		data->termconf->c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
		data->termconf->c_oflag &= ~(OPOST);
	}
	// else if (mode == 1)
	// 	set_read_mode(data);
	else if (mode == 1)
		// 初期の端末設定に戻す
		tcsetattr(STDIN_FILENO, TCSANOW, &default_setting);
}
