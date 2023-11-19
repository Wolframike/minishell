/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:38:14 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/19 15:55:04 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	is_number(char *arg)
{
	if (*arg == '-' || *arg == '+')
		arg++;
	while (*arg != '\0')
	{
		if (!ft_isdigit(*arg))
			return (false);
		arg++;
	}
	return (true);
}

static bool	is_overflow(char *arg)
{
	long	excode;
	long	prev;

	excode = 0;
	while (*arg != '\0')
	{
		prev = excode;
		excode = excode * 10 + (*arg - '0');
		if (prev > excode)
			return (true);
		arg++;
	}
	return (false);
}

int	bi_exit(t_token *token, bool parent)
{
	if (parent)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (token->type != TK_WORD)
		exit(EXIT_SUCCESS);
	if (!is_number(token->word) || is_overflow(token->word))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(token->word, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit(EXIT_SEGV);
	}
	if (can_go_next(token))
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (EXIT_INVAL);
	}
	exit(ft_atoi(token->word) % 256);
}
