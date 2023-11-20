/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:35:47 by knishiok          #+#    #+#             */
/*   Updated: 2023/09/24 22:27:03 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strncat(char *dest, char const *src, size_t nb)
{
	char	*ptr;

	ptr = dest + ft_strlen(dest);
	while (*src != '\0' && nb--)
		*ptr++ = *src++;
	*ptr = '\0';
	return (dest);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	d_nb;
	size_t	s_nb;
	size_t	max_len;

	if (dest == NULL)
		d_nb = 0;
	else
		d_nb = ft_strlen(dest);
	s_nb = ft_strlen(src);
	if (d_nb >= size)
		return (size + s_nb);
	max_len = size - d_nb - 1;
	ft_strncat(dest, src, max_len);
	return (d_nb + s_nb);
}
