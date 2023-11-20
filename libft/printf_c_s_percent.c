/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_c_s_percent.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 02:20:16 by knishiok          #+#    #+#             */
/*   Updated: 2023/10/18 18:28:50 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	printf_c(t_format info, int c, int *len)
{
	char	fill;

	if (info.flags.left_align)
		*len += ft_putchar((char)c);
	if (info.flags.set_width)
	{
		if (info.flags.zero_padding)
			fill = '0';
		else
			fill = ' ';
		while (--info.width)
			*len += ft_putchar(fill);
	}
	if (!info.flags.left_align)
		*len += ft_putchar((char)c);
}

void	printf_s(t_format info, char *s, int *len)
{
	int		s_len;
	int		i;
	char	fill;

	if (s == NULL)
		s = "(null)";
	s_len = ft_strlen(s);
	if (info.precision != -1 && info.precision < s_len)
		s_len = info.precision;
	fill = ' ';
	if (info.flags.zero_padding)
		fill = '0';
	while (!info.flags.left_align && info.width-- > s_len)
		*len += ft_putchar(fill);
	i = 0;
	while (i < s_len)
		*len += ft_putchar(s[i++]);
	while (info.flags.left_align && info.width-- > s_len)
		*len += ft_putchar(fill);
}

void	printf_p(t_format info, void *ptr, int *len)
{
	unsigned char	*addr;
	char			*display;

	if (ptr == NULL)
		display = ft_strdup("0x0");
	else
	{
		addr = (unsigned char *)ptr;
		display = ft_itoa_positive_hex((unsigned long)addr);
	}
	printf_s(info, display, len);
	free(display);
}

void	printf_percent(t_format info, int *len)
{
	char	fill;

	if (info.flags.left_align)
		*len += ft_putchar('%');
	if (info.flags.set_width)
	{
		if (info.flags.zero_padding)
			fill = '0';
		else
			fill = ' ';
		while (--info.width)
			*len += ft_putchar(fill);
	}
	if (!info.flags.left_align)
		*len += ft_putchar('%');
}
