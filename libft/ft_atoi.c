/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:29:53 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/19 22:44:57 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_strtol_decimal(char *str)
{
	long	res;
	int		neg;

	res = 0;
	neg = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str++ == '-')
			neg = 1;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (!neg && (res > (LONG_MAX - (*str - '0')) / 10))
			return (LONG_MAX);
		if (neg && (-res < (LONG_MIN + (*str - '0')) / 10))
			return (LONG_MIN);
		res = res * 10 + (*str++ - '0');
	}
	if (neg)
		res *= -1;
	return (res);
}

int	ft_atoi(const char *str)
{
	return (ft_strtol_decimal((char *)str));
}
