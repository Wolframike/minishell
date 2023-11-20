/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:44:55 by knishiok          #+#    #+#             */
/*   Updated: 2023/09/25 17:32:41 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*to;
	const unsigned char	*from;
	int					i;

	to = (unsigned char *)dst;
	from = (const unsigned char *)src;
	if (to == from || len == 0)
		return (dst);
	if (to > from && to - from < (int)len)
	{
		i = len;
		while (--i >= 0)
			to[i] = from[i];
		return (dst);
	}
	if (from > to && from - to < (int)len)
	{
		i = -1;
		while (++i < (int)len)
			to[i] = from[i];
		return (dst);
	}
	ft_memcpy(dst, src, len);
	return (dst);
}
