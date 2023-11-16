/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpf_printer_hex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 06:59:47 by misargsy          #+#    #+#             */
/*   Updated: 2023/09/27 18:50:28 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ftpf_print_hash(unsigned long n, bool upper, t_format *fstruct)
{
	if (fstruct -> f_hash && n != 0)
	{
		if (upper)
			ft_putstr_fd("0X", STDOUT_FILENO);
		else
			ft_putstr_fd("0x", STDOUT_FILENO);
		return (2);
	}
	return (0);
}

int	ftpf_print_hex(t_format *fstruct, unsigned int n, const char *base)
{
	size_t	width;
	size_t	numlen;
	size_t	fillerlen;
	size_t	total;

	if (fstruct == NULL)
		return (-1);
	total = 0;
	width = fstruct -> width;
	numlen = ftpf_numlen(n, 16, fstruct);
	fillerlen = ftpf_fillerlen(n, 16, fstruct);
	if (ftpf_hash_first(n, fstruct) && n != 0 && fstruct -> f_hash)
		total += ftpf_print_hash(n, (base == HEX_NUM_UC), fstruct);
	total += numlen + fillerlen;
	if (!fstruct -> f_minus)
		while (fillerlen-- > 0)
			ft_putchar_fd(' ', STDOUT_FILENO);
	if (!ftpf_hash_first(n, fstruct) && n != 0 && fstruct -> f_hash)
		total += ftpf_print_hash(n, (base == HEX_NUM_UC), fstruct);
	while (numlen-- > ft_numlen(n, 16))
		ft_putchar_fd('0', STDOUT_FILENO);
	if (!(n == 0 && fstruct -> f_dot && fstruct -> prec == 0))
		ft_putunbr_fd(n, base, STDOUT_FILENO);
	return (ftpf_align(total, width));
}
