/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebuild_dp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 23:11:16 by knishiok          #+#    #+#             */
/*   Updated: 2023/12/05 19:57:28 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	count_patlen(char *line)
{
	int		len;

	len = 0;
	while (*line)
	{
		if (*line != '\'' && *line != '\"')
			len++;
		line++;
	}
	return (len);
}

bool	*expand_or_not(char *line)
{
	bool	*res;
	bool	flg;
	int		i;
	int		pat_len;

	pat_len = count_patlen(line);
	res = (bool *)ft_calloc(pat_len, sizeof(bool));
	if (res == NULL)
		return (NULL);
	flg = false;
	i = 0;
	while (*line)
	{
		if (*line == '\'' || *line == '\"')
			flg = !flg;
		else
		{
			if (*line == '*' && !flg)
				res[i] = true;
			i++;
		}
		line++;
	}
	return (res);
}
