/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpf_printer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 02:36:20 by misargsy          #+#    #+#             */
/*   Updated: 2023/09/29 04:28:15 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ftpf_print_char(t_format *fstruct, char c)
{
	size_t	width;

	if (fstruct == NULL)
		return (-1);
	width = fstruct -> width;
	if (fstruct -> f_minus)
		ft_putchar_fd(c, STDOUT_FILENO);
	while (width > 1)
	{
		if (fstruct -> f_zero)
			ft_putchar_fd('0', STDOUT_FILENO);
		else
			ft_putchar_fd(' ', STDOUT_FILENO);
		width--;
	}
	if (!fstruct -> f_minus)
		ft_putchar_fd(c, STDOUT_FILENO);
	if (fstruct -> width > 1)
		return (fstruct -> width);
	return (1);
}

int	ftpf_print_str(t_format *fstruct, char *str)
{
	size_t	width;
	size_t	cap;

	if (fstruct == NULL)
		return (-1);
	if (str == NULL)
		str = "(null)";
	cap = ft_strlen(str);
	if (fstruct -> f_dot && fstruct -> prec < cap)
		cap = fstruct -> prec;
	width = fstruct -> width;
	if (fstruct -> f_minus)
		ftpf_ps_cap(str, STDOUT_FILENO, fstruct);
	while (width-- > cap)
	{
		if (fstruct -> f_zero)
			ft_putchar_fd('0', STDOUT_FILENO);
		else
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (!fstruct -> f_minus)
		ftpf_ps_cap(str, STDOUT_FILENO, fstruct);
	if (fstruct -> width > cap)
		return (fstruct -> width);
	return (cap);
}

void	ft_putnbr_phex(uintptr_t n, char *base,
		bool prefix, t_format *fstruct)
{
	if (prefix)
		ft_putstr_fd("0x", STDOUT_FILENO);
	if (n >= 16)
		ft_putnbr_phex(n / 16, base, false, fstruct);
	ft_putchar_fd(base[n % 16], STDOUT_FILENO);
}

int	ftpf_print_ptr(t_format *fstruct, void *ptr)
{
	size_t	width;
	size_t	total;

	if (fstruct == NULL)
		return (-1);
	fstruct -> f_hash = true;
	width = fstruct -> width;
	total = ft_ulnumlen((uintptr_t)ptr, 16) + 2;
	if (fstruct -> f_minus)
		ft_putnbr_phex((uintptr_t)ptr, HEX_NUM_LC, 1, fstruct);
	while (width > total)
	{
		if (fstruct -> f_zero)
			ft_putchar_fd('0', STDOUT_FILENO);
		else
			ft_putchar_fd(' ', STDOUT_FILENO);
		width--;
	}
	if (!fstruct -> f_minus)
		ft_putnbr_phex((uintptr_t)ptr, HEX_NUM_LC, 1, fstruct);
	if (fstruct -> width > total)
		return (fstruct -> width);
	return (total);
}

int	ftpf_print_percent(t_format *fstruct)
{
	size_t	width;

	width = fstruct -> width;
	if (fstruct == NULL)
		return (-1);
	if (fstruct -> f_minus)
		ft_putchar_fd('%', STDOUT_FILENO);
	while (width > 1)
	{
		if (fstruct -> f_zero)
			ft_putchar_fd('0', STDOUT_FILENO);
		else
			ft_putchar_fd(' ', STDOUT_FILENO);
		width--;
	}
	if (!fstruct -> f_minus)
		ft_putchar_fd('%', STDOUT_FILENO);
	if (fstruct -> width > 1)
		return (fstruct -> width);
	return (1);
}
