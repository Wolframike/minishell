/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 02:20:09 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/14 17:49:29 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_printulen(t_format info, unsigned int n)
{
	int	res;

	res = 0;
	if (n < 0 || info.flags.sign)
		res++;
	res += digit_count(n, 10);
	return (res);
}

static void	ft_putunbr(t_format *info, unsigned int n, int *len, char putsign)
{
	long long	lnb;
	long long	weight;
	int			print_len;

	ft_putunbr_sub(n, &weight, &lnb);
	print_len = get_printulen(*info, n);
	if (info->precision + (n < 0) > print_len - (putsign == '+'))
	{
		while (--info->precision + (n < 0) >= print_len - (putsign == '+'))
		{
			(*len) += ft_putchar('0');
			info->width--;
		}
		if (n == 0)
			info->precision++;
	}
	if (n == 0 && info->precision == 0)
		return ;
	while (weight)
	{
		(*len) += ft_putchar(lnb / weight + '0');
		lnb %= weight;
		weight /= 10LL;
	}
}

static void	get_putchrs(t_format info,
				unsigned int n, char *fill, char *putsign)
{
	*fill = ' ';
	if (!info.flags.precision && info.flags.zero_padding
		&& !(n == 0 && info.precision == 0))
		*fill = '0';
	*putsign = 'z';
	if (n < 0)
		*putsign = '-';
	else if (info.flags.sign)
		*putsign = '+';
	else if (info.flags.space)
		*putsign = ' ';
}

static int	process_gap(t_format *info, char putsign, unsigned int n, char fill)
{
	int	res;
	int	cmp;

	if (info->flags.left_align)
		cmp = get_printulen(*info, n);
	else
		cmp = ft_max(info->precision + (putsign == '+') + (n < 0),
				get_printulen(*info, n));
	res = 0;
	if (info->width > 0 && n == 0 && info->precision == 0)
		res += ft_putchar(fill);
	while (info->width-- - (putsign == ' ') > cmp)
		res += ft_putchar(fill);
	return (res);
}

void	printf_u(t_format info, unsigned int n, int *len)
{
	char	fill;
	char	putsign;

	get_putchrs(info, n, &fill, &putsign);
	if (!info.flags.left_align)
	{
		if (fill == '0' && putsign != 'z')
		{
			*len += ft_putchar(putsign);
			putsign = 'z';
		}
		*len += process_gap(&info, putsign, n, fill);
		if (putsign != 'z')
			*len += ft_putchar(putsign);
	}
	else if (putsign != 'z')
		*len += ft_putchar(putsign);
	ft_putunbr(&info, n, len, putsign);
	if (info.flags.left_align)
		*len += process_gap(&info, putsign, n, fill);
}
