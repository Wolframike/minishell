/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:19:09 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/22 20:48:22 by misargsy         ###   ########.fr       */
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

int	bi_echo(t_list *args)
{
	bool	nl;

	if (args == NULL)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	nl = nl_option(args->content);
	while (nl_option(args->content))
	{
		if (args->next == NULL)
			return (EXIT_SUCCESS);
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
	return (EXIT_SUCCESS);
}
