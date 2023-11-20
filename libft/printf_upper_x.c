/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_upper_x.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 06:59:43 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/14 17:49:42 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putxnbr_upper(t_format *info, unsigned int n,
			int *len, char putsign)
{
	long long	lnb;
	long long	weight;
	int			print_len;

	ft_putxnbr_sub(n, &weight, &lnb);
	print_len = get_printhlen(*info, n);
	if (info->flags.sharp && n)
		*len += ft_putstr("0X");
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
	print_hex(weight, lnb, true, len);
}

void	printf_x_upper(t_format info, unsigned int n, int *len)
{
	char	fill;
	char	putsign;

	if (info.flags.sharp && n)
		info.width -= 2;
	get_puthchrs(info, n, &fill, &putsign);
	if (!info.flags.left_align)
	{
		if (fill == '0' && putsign != 'z')
		{
			*len += ft_putchar(putsign);
			putsign = 'z';
		}
		*len += process_hgap(&info, putsign, n, fill);
		if (putsign != 'z')
			*len += ft_putchar(putsign);
	}
	else if (putsign != 'z')
		*len += ft_putchar(putsign);
	ft_putxnbr_upper(&info, n, len, putsign);
	if (info.flags.left_align)
		*len += process_hgap(&info, putsign, n, fill);
}
