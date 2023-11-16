/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 01:21:39 by misargsy          #+#    #+#             */
/*   Updated: 2023/09/29 02:31:22 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t count)
{
	unsigned char			*cdest;
	const unsigned char		*csrc;
	size_t					i;

	if (dest == NULL && src == NULL)
		return (NULL);
	cdest = (unsigned char *)dest;
	csrc = (const unsigned char *)src;
	i = 0;
	while (i < count)
	{
		cdest[i] = csrc[i];
		i++;
	}
	return (dest);
}
