/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 02:30:39 by misargsy          #+#    #+#             */
/*   Updated: 2023/09/21 10:50:02 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	l;

	l = ft_strlen(s);
	while (l > 0)
	{
		if (s[l] == (char)c)
			return ((char *)s + l);
		l--;
	}
	if (l == 0 && s[l] == (char)c)
		return ((char *)s);
	return (NULL);
}
