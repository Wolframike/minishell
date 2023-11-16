/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 23:16:15 by misargsy          #+#    #+#             */
/*   Updated: 2023/09/30 10:45:57 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_charset(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i++])
			return (1);
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	s;
	size_t	e;

	if (s1 == NULL || set == NULL)
		return (NULL);
	s = 0;
	e = ft_strlen(s1) - 1;
	while (in_charset(s1[s], set))
		s++;
	while (in_charset(s1[e], set))
		e--;
	if (e < s)
		return (ft_strdup(""));
	return (ft_substr(s1, s, e - s + 1));
}
