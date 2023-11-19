/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:19:09 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/18 20:03:45 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	nl_option(char *arg)
{
	size_t	i;

	i = 0;
	if (arg[i++] != '-')
		return (true);
	while (arg[i] != '\0')
	{
		if (arg[i] != 'n')
			return (true);
		i++;
	}
	return (false);
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
	if (!nl)
		token = token->next;
	while (token->next != NULL && token->next->type == TK_WORD)
	{
		ft_putstr_fd(token->word, STDOUT_FILENO);
		ft_putchar_fd(' ', STDOUT_FILENO);
		token = token->next;
	}
	ft_putstr_fd(token->word, STDOUT_FILENO);
	if (nl)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
