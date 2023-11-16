/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpf_printer_cond.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 05:34:30 by misargsy          #+#    #+#             */
/*   Updated: 2023/09/30 19:46:06 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

bool	ftpf_sign_first(int n, t_format *fstruct)
{
	size_t	width;
	size_t	numlen;

	width = fstruct -> width;
	numlen = ftpf_numlen(n, 10, fstruct);
	return ((n < 0 || fstruct -> f_plus || fstruct -> f_space)
		&& (fstruct -> f_minus || (fstruct -> f_zero && !fstruct -> f_dot)
			|| numlen > width));
}

bool	ftpf_hash_first(unsigned long n, t_format *fstruct)
{
	size_t	width;
	size_t	numlen;

	width = fstruct -> width;
	numlen = ftpf_numlen(n, 16, fstruct);
	return (fstruct -> f_hash && n != 0
		&& (fstruct -> f_minus || (fstruct -> f_zero && !fstruct -> f_dot)
			|| numlen > width));
}

size_t	ftpf_fillerlen(long long n, int base, t_format *fstruct)
{
	size_t	numlen;
	size_t	fillerlen;

	numlen = ftpf_numlen(n, base, fstruct);
	if (fstruct -> f_minus)
		return (0);
	if (fstruct -> f_dot && fstruct -> prec >= numlen)
		fillerlen = fstruct -> prec - numlen;
	if (fstruct -> width < numlen)
		fillerlen = 0;
	else
		fillerlen = fstruct -> width - numlen;
	if ((fstruct -> f_space || fstruct -> f_plus || n < 0) && fillerlen > 0)
		fillerlen--;
	if (fstruct -> f_hash && n != 0)
	{
		if (fillerlen > 1)
			fillerlen -= 2;
		else
			fillerlen = 0;
	}
	return (fillerlen);
}
