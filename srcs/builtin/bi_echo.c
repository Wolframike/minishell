/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:19:09 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/19 16:10:52 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	nl_option(char *arg)
{
	size_t	i;

	i = 0;
	if (arg[i++] != '-')
		return (false);
	while (arg[i] != '\0')
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	bi_echo(t_token *token)
{
	bool	nl;

	if (token == NULL)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	nl = nl_option(token->word);
	while (nl_option(token->word))
	{
		if (!can_go_next(token))
			return (EXIT_SUCCESS);
		token = token->next;
	}
	while (true)
	{
		ft_putstr_fd(token->word, STDOUT_FILENO);
		if (!can_go_next(token))
			break ;
		token = token->next;
		ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (!nl)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
