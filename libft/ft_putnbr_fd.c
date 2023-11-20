/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:47:23 by knishiok          #+#    #+#             */
/*   Updated: 2023/09/24 22:27:03 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long long	lnb;
	long long	weight;

	lnb = (long long)n;
	weight = 1LL;
	if (lnb < 0LL)
	{
		lnb *= -1LL;
		ft_putchar_fd('-', fd);
	}
	while (lnb >= weight * 10LL)
		weight *= 10LL;
	while (weight)
	{
		ft_putchar_fd(lnb / weight + '0', fd);
		lnb %= weight;
		weight /= 10LL;
	}
}
