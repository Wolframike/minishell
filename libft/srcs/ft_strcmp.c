/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 19:11:12 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/13 17:45:06 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	while (((*str1 != '\0')) && (*str2 != '\0'))
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if ((*str1 == '\0') && (*str2 != '\0'))
		return (-(*str2));
	else if ((*str1 != '\0') && (*str2 == '\0'))
		return (*str1);
	return (0);
}
