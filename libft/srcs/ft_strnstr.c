/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 02:59:48 by misargsy          #+#    #+#             */
/*   Updated: 2023/09/20 21:53:56 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	char	*s;
	char	*t;
	size_t	i;

	if (str == NULL && n == 0)
		return (NULL);
	if (n < 0 || to_find[0] == '\0')
		return ((char *)str);
	i = 0;
	while (*str != '\0')
	{
		s = (char *)str;
		t = (char *)to_find;
		while ((*t != '\0') && (*s == *t) && (i + (s - str) < n))
		{
			s++;
			t++;
		}
		if (*t == '\0')
			return ((char *)str);
		str++;
		i++;
	}
	return (NULL);
}
