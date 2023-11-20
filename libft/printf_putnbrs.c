/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 05:20:27 by knishiok          #+#    #+#             */
/*   Updated: 2023/10/18 18:28:50 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_sub(int n, long long *weight, long long *lnb)
{
	*lnb = (long)n;
	*weight = 1LL;
	if (*lnb < 0)
		*lnb *= -1;
	while (*lnb >= 10LL * *weight)
		*weight *= 10LL;
}

void	ft_putunbr_sub(unsigned int n, long long *weight, long long *lnb)
{
	*lnb = (long)n;
	*weight = 1LL;
	if (*lnb < 0)
		*lnb *= -1;
	while (*lnb >= 10LL * *weight)
		*weight *= 10LL;
}

void	ft_putxnbr_sub(unsigned int n, long long *weight, long long *lnb)
{
	*lnb = (long)n;
	*weight = 1LL;
	if (*lnb < 0)
		*lnb *= -1;
	while (*lnb >= 16LL * *weight)
		*weight *= 16LL;
}

void	print_hex(long long weight, long long lnb, bool is_large, int *len)
{
	while (weight)
	{
		if (is_large)
			(*len) += ft_putchar(UPPER_HEX[lnb / weight]);
		else
			(*len) += ft_putchar(LOWER_HEX[lnb / weight]);
		lnb %= weight;
		weight /= 16LL;
	}
}
