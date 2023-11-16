/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 08:55:14 by misargsy          #+#    #+#             */
/*   Updated: 2023/09/29 03:21:49 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	numcatch(const char *str)
{
	long	n;
	long	m;

	n = 0;
	while (('0' <= *str) && (*str <= '9'))
	{
		m = n;
		n = n * 10 + (*str - '0');
		if (n < m)
			return (-1);
		str++;
	}
	return (n);
}

unsigned int	ft_atoui(const char *str)
{
	long	val;

	val = 0;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if ('0' <= *str && *str <= '9')
		val = numcatch(str);
	if (val == -1)
		return (INT_MAX);
	return ((int)val);
}

void	ftpf_ps_cap(char *str, int fd, t_format *fstruct)
{
	size_t	cap;
	size_t	n;

	cap = ft_strlen(str);
	n = 0;
	if (fstruct -> f_dot == 1 && fstruct -> prec < cap)
		cap = fstruct -> prec;
	while (n < cap)
	{
		ft_putchar_fd(str[n], fd);
		n++;
	}
}

void	ft_putunbr_fd(uintmax_t n, const char *base, int fd)
{
	size_t	baselen;

	baselen = ft_strlen(base);
	if (n >= baselen)
		ft_putunbr_fd(n / baselen, base, fd);
	ft_putchar_fd(base[n % baselen], fd);
}

size_t	ftpf_putsign_fd(int n, int fd)
{
	if (n < 0)
		ft_putchar_fd('-', fd);
	else
		ft_putchar_fd('+', fd);
	return (1);
}
