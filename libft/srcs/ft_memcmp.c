/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 02:55:55 by misargsy          #+#    #+#             */
/*   Updated: 2023/09/29 02:30:31 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *buf1, const void *buf2, size_t count)
{
	while (count > 0)
	{
		if (*(const unsigned char *)buf1 != *(const unsigned char *)buf2)
			return (*(const unsigned char *)buf1
				- *(const unsigned char *)buf2);
		count--;
		buf1++;
		buf2++;
	}
	if (count == 0)
		return (0);
	return (*(const unsigned char *)buf1 - *(const unsigned char *)buf2);
}
