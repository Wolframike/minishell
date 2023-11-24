/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:18:54 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/24 23:25:42 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <dirent.h>

int	bi_cd(t_list *args)
{
	if (args == NULL)
	{
		if (!move_to_envvar("HOME"))
			return (EXIT_KO);
		return (EXIT_OK);
	}
	if (ft_strcmp(args->content, "-") == 0)
	{
		if (!move_to_envvar("OLDPWD"))
			return (EXIT_KO);
		return (EXIT_OK);
	}
	else
	{
		if (!move_to_path(args->content))
			return (EXIT_KO);
		return (EXIT_OK);
	}
}
