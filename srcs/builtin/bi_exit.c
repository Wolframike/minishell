/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:38:14 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/11 06:10:19 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	isnum(char *arg)
{
	while (*arg == ' ')
		arg++;
	if (*arg == '-' || *arg == '+')
		arg++;
	if (*arg == '\0')
		return (false);
	while (*arg != '\0')
	{
		if (*arg == ' ')
			break ;
		if (!ft_isdigit(*arg))
			return (false);
		arg++;
	}
	while (*arg == ' ' && *arg != '\0')
		arg++;
	return (*arg == '\0');
}

static bool	isoverflow(char *arg)
{
	long	excode;
	long	prev;

	excode = 0;
	while (*arg == ' ')
		arg++;
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
		return (EXIT_KO);
	}
	exit(ft_atoi(args->content) % 256);
}
