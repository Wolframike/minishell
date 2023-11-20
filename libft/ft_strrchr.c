/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:26:15 by knishiok          #+#    #+#             */
/*   Updated: 2023/09/24 22:27:45 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ret;
	int		i;
	char	c1;

	ret = NULL;
	i = -1;
	c1 = (char)c;
	while (s[++i])
	{
		if (s[i] == c1)
			ret = (char *)(s + i);
	}
	if (c == 0 && s[i] == 0)
		ret = (char *)(s + i);
	return (ret);
}
