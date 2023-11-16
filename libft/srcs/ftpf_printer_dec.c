/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpf_printer_dec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 07:52:42 by misargsy          #+#    #+#             */
/*   Updated: 2023/09/30 19:42:44 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ftpf_numlen(long long n, int base, t_format *fstruct)
{
	size_t	numlen;

	numlen = 0;
	if (n == 0 && fstruct -> f_dot && !fstruct -> prec)
		return (0);
	numlen = ft_numlen(n, base);
	if (fstruct -> f_dot && fstruct -> prec > numlen)
		numlen = fstruct -> prec;
	if (!fstruct -> f_minus && fstruct -> f_zero && !fstruct -> f_dot
		&& fstruct -> width > numlen)
	{
		if (n >= 0 && (fstruct -> f_plus + fstruct -> f_space <= 1))
			numlen = fstruct -> width - fstruct -> f_plus - fstruct -> f_space;
		else
			numlen = fstruct -> width - 1;
	}
	return (numlen);
}

int	ftpf_print_sign(int n, t_format *fstruct)
{
	if (n < 0 || fstruct -> f_plus || fstruct -> f_space)
	{
		if (n < 0)
			ft_putchar_fd('-', STDOUT_FILENO);
		else if (fstruct -> f_plus)
			ft_putchar_fd('+', STDOUT_FILENO);
		else if (fstruct -> f_space)
			ft_putchar_fd(' ', STDOUT_FILENO);
		return (1);
	}
	return (0);
}

size_t	ftpf_align(size_t total, size_t width)
{
	size_t	w;

	w = width;
	while (w > total)
	{
		ft_putchar_fd(' ', STDOUT_FILENO);
		w--;
	}
	if (width > total)
		return (width);
	return (total);
}

int	ftpf_print_int(t_format *fstruct, int n)
{
	size_t	width;
	size_t	numlen;
	size_t	fillerlen;
	size_t	total;

	if (fstruct == NULL)
		return (-1);
	total = 0;
	width = fstruct -> width;
	numlen = ftpf_numlen(n, 10, fstruct);
	fillerlen = ftpf_fillerlen(n, 10, fstruct);
	if (ftpf_sign_first(n, fstruct))
		total += ftpf_print_sign(n, fstruct);
	total += numlen + fillerlen;
	if (!fstruct -> f_minus)
		while (fillerlen-- > 0)
			ft_putchar_fd(' ', STDOUT_FILENO);
	if (!ftpf_sign_first(n, fstruct))
		total += ftpf_print_sign(n, fstruct);
	while (numlen-- > ft_numlen(n, 10))
		ft_putchar_fd('0', STDOUT_FILENO);
	if (!(n == 0 && fstruct -> f_dot && fstruct -> prec == 0))
		ft_putabsnbr_fd(n, STDOUT_FILENO);
	return (ftpf_align(total, width));
}

int	ftpf_print_uint(t_format *fstruct, unsigned int n)
{
	size_t	width;
	size_t	numlen;
	size_t	fillerlen;
	size_t	total;

	if (fstruct == NULL)
		return (-1);
	total = 0;
	width = fstruct -> width;
	numlen = ftpf_numlen(n, 10, fstruct);
	fillerlen = ftpf_fillerlen(n, 10, fstruct);
	total += numlen + fillerlen;
	if (!fstruct -> f_minus)
		while (fillerlen-- > 0)
			ft_putchar_fd(' ', STDOUT_FILENO);
	while (numlen-- > ft_numlen(n, 10))
		ft_putchar_fd('0', STDOUT_FILENO);
	if (!(n == 0 && fstruct -> f_dot && fstruct -> prec == 0))
		ft_putabsnbr_fd(n, STDOUT_FILENO);
	return (ftpf_align(total, width));
}
