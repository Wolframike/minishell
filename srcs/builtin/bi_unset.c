/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:26:59 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/25 15:28:29 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	is_valid_identifier(char *str)
{
	size_t	i;

	i = 0;
	if ((ft_isalpha(str[i]) == 0) && (str[i] != '_'))
		return (false);
	i++;
	while (str[i] != '\0')
	{
		if ((ft_isalnum(str[i]) == 0) && (str[i] != '_'))
			return (false);
		i++;
	}
	return (true);
}

static void	unset_var(char *varname)
{
	size_t	i;
	size_t	j;
	size_t	varlen;

	i = 0;
	varlen = ft_strlen(varname);
	while (environ[i] != NULL)
	{
		if (ft_strncmp(environ[i], varname, varlen) == 0)
		{
			j = i;
			while (environ[j] != NULL)
			{
				environ[j] = environ[j + 1];
				j++;
			}
			return ;
		}
		i++;
	}
}

int	bi_unset(t_list *args)
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
		unset_var(varname);
		args = args->next;
	}
	return (EXIT_OK);
}
