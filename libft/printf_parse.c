/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:56:38 by knishiok          #+#    #+#             */
/*   Updated: 2023/10/18 18:28:50 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_format	create_new_format(void)
{
	t_format	fmt;

	fmt.flags.left_align = false;
	fmt.flags.zero_padding = false;
	fmt.flags.sign = false;
	fmt.flags.sharp = false;
	fmt.flags.period = false;
	fmt.flags.space = false;
	fmt.flags.set_width = false;
	fmt.precision = -1;
	fmt.width = 0;
	return (fmt);
}

static void	parse_sub2(const char ***s, t_format *fmt)
{
	if (***s == '-')
	{
		fmt->flags.left_align = true;
		fmt->flags.zero_padding = false;
	}
	else if (***s == '0')
	{
		if (!fmt->flags.left_align)
			fmt->flags.zero_padding = true;
	}
	else if (***s >= '1' && ***s <= '9')
	{
		fmt->flags.set_width = true;
		fmt->width = ft_atoi((const char *)*s);
		(**s)--;
	}
}

static void	parse_sub(const char ***s, t_format *fmt)
{
	if (***s == '-' || ***s == '0' || (***s >= '0' && ***s <= '9'))
		parse_sub2(s, fmt);
	else if (***s == ' ')
		fmt->flags.space = true;
	else if (***s == '+')
		fmt->flags.sign = true;
	else if (***s == '#')
		fmt->flags.sharp = true;
	else if (***s == '.')
	{
		fmt->flags.period = true;
		(**s)++;
		if ((***s >= '0' && ***s <= '9') || ft_strchr(SPECIFIER, ***s))
		{
			fmt->flags.precision = true;
			fmt->precision = ft_atoi((const char *)*s);
			(**s)--;
		}
		else
			fmt->flags.period = false;
	}
	(**s)++;
}

t_format	parse_flags(const char **s)
{
	t_format	fmt;

	fmt = create_new_format();
	while (!ft_strchr(SPECIFIER, **s))
		parse_sub(&s, &fmt);
	return (fmt);
}
