/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 17:22:50 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/26 17:22:58 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

bool	is_valid_identifier(char *str)
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
