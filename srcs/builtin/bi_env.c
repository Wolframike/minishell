/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:30:37 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/24 18:42:28 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	bi_env(void)
{
	size_t	i;

	if (environ == NULL)
		return (EXIT_OK);
	i = 0;
	while (environ[i] != NULL)
	{
		ft_putstr_fd(environ[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	return (EXIT_OK);
}
