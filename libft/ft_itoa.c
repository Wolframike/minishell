/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:42:35 by knishiok          #+#    #+#             */
/*   Updated: 2023/10/18 18:28:18 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	long long	lnb;
	int			is_negative;
	int			digit;
	char		*result;

	lnb = n;
	is_negative = n < 0;
	digit = digit_count(n, 10);
	result = (char *)malloc(sizeof(char) * (digit + is_negative + 1));
	if (result == NULL)
		return (result);
	result[digit + is_negative] = '\0';
	if (is_negative)
	{
		result[0] = '-';
		lnb *= -1;
	}
	while (digit--)
	{
		result[is_negative + digit] = lnb % 10 + '0';
		lnb /= 10;
	}
	return (result);
}
