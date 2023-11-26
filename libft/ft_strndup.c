/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:23:59 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/26 12:56:27 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *src, size_t len)
{
	size_t		i;
	char		*res;

	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (src[i] && i < len)
	{
		res[i] = src[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
