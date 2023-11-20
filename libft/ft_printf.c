/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:24:23 by knishiok          #+#    #+#             */
/*   Updated: 2023/10/18 18:28:50 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printf_out(t_format info, va_list *args, char c, int *len)
{
	if (c == 's')
		printf_s(info, va_arg(*args, char *), len);
	else if (c == 'c')
		printf_c(info, va_arg(*args, int), len);
	else if (c == 'd' || c == 'i')
		printf_d_i(info, va_arg(*args, int), len);
	else if (c == 'u')
		printf_u(info, va_arg(*args, unsigned int), len);
	else if (c == 'x')
		printf_x(info, va_arg(*args, unsigned int), len);
	else if (c == 'X')
		printf_x_upper(info, va_arg(*args, unsigned int), len);
	else if (c == 'p')
		printf_p(info, va_arg(*args, void *), len);
	else if (c == '%')
		printf_percent(info, len);
}

int	ft_printf(const char *fmt, ...)
{
	int			len;
	va_list		args;
	t_format	info;

	len = 0;
	va_start(args, fmt);
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			if (*fmt)
				info = parse_flags(&fmt);
			ft_printf_out(info, &args, *fmt++, &len);
		}
		else
			len += ft_putchar(*fmt++);
	}
	return (len);
}
