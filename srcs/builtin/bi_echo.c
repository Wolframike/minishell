/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:19:09 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/01 16:35:52 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	nl_option(char *arg)
{
	size_t	i;

	i = 0;
	if (arg[i++] != '-')
		return (false);
	if (arg[i++] != 'n')
		return (false);
	while (arg[i] != '\0')
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	bi_echo(t_list *args, t_exec *config)
{
	bool	nl;

	(void)config;
	if (args == NULL)
		return (ft_putchar_fd('\n', STDOUT_FILENO), EXIT_OK);
	nl = nl_option(args->content);
	while (nl_option(args->content))
	{
		if (args->next == NULL)
			return (EXIT_OK);
		args = args->next;
	}
	while (true)
	{
		ft_putstr_fd(args->content, STDOUT_FILENO);
		if (args->next == NULL)
			break ;
		args = args->next;
		ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (!nl)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_OK);
}
