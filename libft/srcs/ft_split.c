/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 02:23:17 by misargsy          #+#    #+#             */
/*   Updated: 2023/09/28 16:05:44 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	wcount(const char *str, const char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c && str[i] != '\0')
			i++;
		if (str[i] != c && str[i] != '\0')
			count++;
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	return (count);
}

static size_t	wlen(const char *str, const char c)
{
	size_t	len;

	len = 0;
	while (*str != c && *str != '\0')
	{
		len++;
		str++;
	}
	return (len);
}

static char	**freeall(char **s, size_t i)
{
	while (i > 0)
	{
		free(s[i]);
		i--;
	}
	free(s);
	return (NULL);
}

char	**ft_split(const char *str, const char c)
{
	char	**s;
	size_t	i;
	size_t	w;

	if (!str)
		return (NULL);
	w = wcount(str, c);
	s = (char **)malloc(sizeof(char *) * (w + 1));
	if (s == NULL)
		return (NULL);
	s[w] = NULL;
	i = 0;
	while (w > 0)
	{
		while (*str == c && *str != '\0')
			str++;
		s[i] = ft_substr(str, 0, wlen(str, c));
		if (s[i] == NULL)
			return (freeall(s, i));
		while (*str != c && *str != '\0')
			str++;
		i++;
		w--;
	}
	return (s);
}
