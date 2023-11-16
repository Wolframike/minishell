/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpf_is.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 03:00:41 by misargsy          #+#    #+#             */
/*   Updated: 2023/09/26 05:24:14 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

bool	is_flag(const char c)
{
	size_t	i;

	i = 0;
	while (FLAGS[i] != '\0')
	{
		if (FLAGS[i] == c)
			return (true);
		i++;
	}
	return (false);
}

bool	is_conv(const char c)
{
	size_t	i;

	i = 0;
	while (CONVS[i] != '\0')
	{
		if (CONVS[i] == c)
			return (true);
		i++;
	}
	return (false);
}
