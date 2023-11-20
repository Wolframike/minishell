/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:01:43 by knishiok          #+#    #+#             */
/*   Updated: 2023/10/29 14:36:13 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	size_t	substr_len;
	char	*substr;

	if (s == NULL)
		return (NULL);
	s_len = (size_t)ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	substr_len = (size_t)ft_min(s_len - start, len);
	substr = (char *)malloc((substr_len + 1) * sizeof(char));
	if (substr == NULL)
		return (NULL);
	i = 0;
	while (i < substr_len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[substr_len] = '\0';
	return (substr);
}
