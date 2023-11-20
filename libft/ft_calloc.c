/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:05:20 by knishiok          #+#    #+#             */
/*   Updated: 2023/09/24 22:27:03 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	detect_overflow(size_t n1, size_t n2)
{
	size_t	max_val;

	if (n1 == 0 || n2 == 0)
		return (0);
	max_val = SIZE_MAX / n1;
	if (n2 > max_val)
		return (1);
	return (0);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total_size;

	if (detect_overflow(count, size))
		return (malloc(SIZE_MAX));
	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	total_size = count * size;
	ptr = malloc(total_size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, total_size);
	return (ptr);
}
