/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:43:45 by knishiok          #+#    #+#             */
/*   Updated: 2023/09/24 22:27:03 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*result;
	size_t		start;
	size_t		end;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]) != NULL)
		start++;
	if (start == ft_strlen(s1))
		return (ft_strdup(""));
	end = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[end]) != NULL)
		end--;
	result = (char *)malloc(sizeof(char) * (end - start + 2));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s1 + start, end - start + 2);
	return (result);
}
