/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 02:37:16 by misargsy          #+#    #+#             */
/*   Updated: 2023/09/21 18:33:19 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t count)
{
	if ((str1 == NULL || str2 == NULL) && count == 0)
		return (0);
	while (((*str1 != '\0')) && (*str2 != '\0') && (count > 0))
	{
		if (*str1 != *str2)
			return (*(unsigned char *)str1 - *(unsigned char *)str2);
		count--;
		str1++;
		str2++;
	}
	if (count == 0)
		return (0);
	return (*(unsigned char *)str1 - *(unsigned char *)str2);
}
