/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 23:37:18 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/13 18:52:27 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ftpf_phelper(char c, t_format *fstruct, va_list args)
{
	if (c == 'c')
		return (ftpf_print_char(fstruct, va_arg(args, int)));
	else if (c == 's')
		return (ftpf_print_str(fstruct, va_arg(args, char *)));
	else if (c == 'p')
		return (ftpf_print_ptr(fstruct, va_arg(args, void *)));
	else if (c == 'd' || c == 'i')
		return (ftpf_print_int(fstruct, va_arg(args, int)));
	else if (c == 'u')
		return (ftpf_print_uint(fstruct, va_arg(args, unsigned int)));
	else if (c == 'x')
		return (ftpf_print_hex(fstruct,
				va_arg(args, unsigned int), HEX_NUM_LC));
	else if (c == 'X')
		return (ftpf_print_hex(fstruct,
				va_arg(args, unsigned int), HEX_NUM_UC));
	else if (c == '%')
		return (ftpf_print_percent(fstruct));
	return (-1);
}

ssize_t	ftpf_printer(char **format, va_list args)
{
	size_t		i;
	ssize_t		n;
	t_format	*fstruct;

	i = 1;
	n = 0;
	while ((*format)[i] != '\0' && !is_conv((*format)[i]))
		i++;
	fstruct = ftpf_fparse(*format);
	if (fstruct == NULL)
		return (-1);
	n = ftpf_phelper((*format)[i], fstruct, args);
	*format += i;
	free(fstruct);
	return (n);
}

ssize_t	ftpf_main(char *format, va_list args)
{
	ssize_t	n;
	size_t	total;

	n = 0;
	total = 0;
	while (*format != '\0')
	{
		if (*format == '%')
		{
			n = ftpf_printer(&format, args);
			if (n == -1)
				return (-1);
			total += n;
		}
		else
		{
			ft_putchar_fd(*format, STDOUT_FILENO);
			total++;
		}
		format++;
	}
	return (total);
}

int	ft_dprintf(const int fd, const char	*format, ...)
{
	va_list	args;
	char	*fcopy;
	int		total;
	int		stdout;

	stdout = dup(STDOUT_FILENO);
	if (stdout == -1)
		return (-1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (-1);
	fcopy = ft_strdup(format);
	if (fcopy == NULL)
		return (-1);
	va_start(args, format);
	total = ftpf_main(fcopy, args);
	if (total < 0)
		return (-1);
	va_end(args);
	free(fcopy);
	if (dup2(stdout, STDOUT_FILENO) == -1)
		return (-1);
	return (total);
}
