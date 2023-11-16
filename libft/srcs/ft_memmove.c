/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 01:24:34 by misargsy          #+#    #+#             */
/*   Updated: 2023/09/29 02:30:58 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t count)
{
	unsigned char		*ptr;
	const unsigned char	*ptr2;

	if (dest == NULL && src == NULL)
		return (NULL);
	ptr = (unsigned char *)dest;
	ptr2 = (const unsigned char *)src;
	if (ptr2 < ptr)
	{
		while (count-- > 0)
		{
			ptr[count] = ptr2[count];
		}
	}
	else
	{
		while (count-- > 0)
		{
			*ptr = *ptr2;
			ptr++;
			ptr2++;
		}
	}
	return (dest);
}
