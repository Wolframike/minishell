/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:56:49 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/18 15:56:57 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, size_t n)
{
	char	*dest;
	size_t	l;

	l = ft_strlen(src);
	if (n < l)
		l = n;
	dest = (char *)malloc(sizeof(char) * (l + 1));
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, src, l + 1);
	return (dest);
}
