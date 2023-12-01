/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:13:07 by knishiok          #+#    #+#             */
/*   Updated: 2023/12/01 21:13:57 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"

void	set_idle_handler(void)
{
	struct sigaction	sig;

	sig.sa_handler = idle_handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGINT, &sig, NULL);
	sig.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sig, NULL);
}

void	set_exec_handler(bool wait_child)
{
	struct sigaction	sig;

	sig.sa_handler = SIG_IGN;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGQUIT, &sig, NULL);
	if (wait_child == false)
		sig.sa_handler = exec_handler;
	sigaction(SIGINT, &sig, NULL);
}

void	set_exec_child_handler(void)
{
	struct sigaction	sig;

	sig.sa_handler = SIG_DFL;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
}

void	set_heredoc_handler(void)
{
	struct sigaction	sig;

	sig.sa_handler = heredoc_handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGINT, &sig, NULL);
	sig.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sig, NULL);
}

void	set_heredoc_child_handler(void)
{
	struct sigaction	sig;

	sig.sa_handler = SIG_IGN;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGQUIT, &sig, NULL);
	sig.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sig, NULL);
}
