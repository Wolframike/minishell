/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftpf_fparse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 03:39:25 by misargsy          #+#    #+#             */
/*   Updated: 2023/09/30 19:19:05 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_format	*fstruct_init(void)
{
	t_format	*fstruct;

	fstruct = malloc(sizeof(t_format));
	if (!fstruct)
		return (NULL);
	fstruct->f_plus = false;
	fstruct->f_minus = false;
	fstruct->f_zero = false;
	fstruct->f_space = false;
	fstruct->f_dot = false;
	fstruct->f_hash = false;
	fstruct->width = false;
	return (fstruct);
}

size_t	get_width(char *format)
{
	size_t	width;

	width = 0;
	while (*format != '%')
		format--;
	format++;
	while (is_flag(*format) && *format != '.' && *format != '\0')
		format++;
	width = ft_atoui(format);
	return (width);
}

size_t	get_prec(char *format, t_format *fstruct)
{
	size_t	prec;

	prec = 0;
	if (fstruct -> f_dot)
	{
		while (*format != '.' )
			format--;
		format++;
		prec = ft_atoui(format);
	}
	return (prec);
}

bool	get_zero(char *format)
{
	bool	i;

	i = false;
	while (*format != '%')
		format--;
	while (!ft_isdigit(*format) && *format != '\0')
		format++;
	if (*format == '0')
		i = true;
	return (i);
}

t_format	*ftpf_fparse(char *format)
{
	t_format	*fstruct;

	format++;
	fstruct = fstruct_init();
	if (!fstruct)
		return (NULL);
	while (!is_conv(*format) && *format != '\0')
	{
		if (*format == '+')
			fstruct -> f_plus = true;
		else if (*format == '-')
			fstruct -> f_minus = true;
		else if (*format == ' ')
			fstruct -> f_space = true;
		else if (*format == '.')
			fstruct -> f_dot = true;
		else if (*format == '#')
			fstruct -> f_hash = true;
		format++;
	}
	fstruct -> width = get_width(format);
	fstruct -> prec = get_prec(format, fstruct);
	fstruct -> f_zero = get_zero(format);
	return (fstruct);
}
