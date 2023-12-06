/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:38:14 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/06 22:48:17 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	isnum(char *arg)
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

static bool	isoverflow(char *arg)
{
	long	excode;
	long	prev;

	excode = 0;
	if (*arg == '-' || *arg == '+')
		arg++;
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

int	bi_exit(t_list *args, bool parent, t_exec *config)
{
	if (parent)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (args == NULL)
		exit(config->exit_code);
	if (!isnum(args->content) || isoverflow(args->content))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args->content, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit(EXIT_SEGV);
	}
	if (args->next != NULL)
	{
		too_many_arguments("exit");
		return (EXIT_INVAL);
	}
	exit(ft_atoi(args->content) % 256);
}
