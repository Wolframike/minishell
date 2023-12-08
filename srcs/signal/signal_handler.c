/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:21:15 by knishiok          #+#    #+#             */
/*   Updated: 2023/12/08 22:09:43 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"

void	idle_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = SIGINT;
		ft_putchar_fd('\n', STDERR_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	heredoc_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = SIGINT;
		ft_putchar_fd('\n', STDERR_FILENO);
	}
}

void	exec_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = signum;
		ft_putchar_fd('\n', STDERR_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	if (signum == SIGQUIT)
	{
		g_signal = signum;
		ft_putendl_fd("Quit: 3", STDERR_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}
