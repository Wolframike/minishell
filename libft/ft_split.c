/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:40:19 by knishiok          #+#    #+#             */
/*   Updated: 2023/09/25 17:37:20 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strndup(char *src, int len)
{
	int		i;
	char	*res;

	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (src[i] && i < len)
	{
		res[i] = src[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

static int	split_word(char const *s, char c, char **result)
{
	int		i;
	char	*word_start;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			word_start = (char *)s;
			while (*s && *s != c)
				s++;
			result[i] = ft_strndup(word_start, s - word_start);
			if (result[i++] == NULL)
			{
				while (--i >= 0)
					free(result[i]);
				free(result);
				return (-1);
			}
		}
		else
			s++;
	}
	return (i);
}

static int	word_count(char const *s, char c)
{
	int		word_number;
	int		flg;
	int		i;

	word_number = 0;
	flg = 0;
	i = 0;
	while (s[i])
	{
		if (s[i++] == c)
			flg = 0;
		else if (!flg)
		{
			flg = 1;
			word_number++;
		}
	}
	return (word_number);
}

char	**ft_split(char const *s, char c)
{
	int		word_number;
	char	**ret;

	if (s == NULL)
		return (NULL);
	word_number = word_count(s, c);
	ret = (char **)malloc((word_number + 1) * sizeof(char *));
	if (ret == NULL)
		return (NULL);
	if (split_word(s, c, ret) == -1)
		return (NULL);
	ret[word_number] = 0;
	return (ret);
}
