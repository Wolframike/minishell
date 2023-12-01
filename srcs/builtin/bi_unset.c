/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:26:59 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/01 16:28:28 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	bi_unset(t_list *args, t_exec *config)
{
	char	*varname;

	while (args != NULL)
	{
		varname = args->content;
		if (!is_valid_identifier(varname))
		{
			not_a_valid_identifier("unset", varname);
			return (EXIT_KO);
		}
		unset_env(&(config->env), varname);
		args = args->next;
	}
	return (EXIT_OK);
}
