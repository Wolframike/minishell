/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   judge_matched.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 21:44:40 by knishiok          #+#    #+#             */
/*   Updated: 2023/12/03 23:31:42 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static void	destroy_table(bool **table, int height)
{
	while (height >= 0)
		free(table[height--]);
	free(table);
}

static bool	**create_table(char *filename, char *pattern, bool *flg)
{
	int		i;
	bool	**table;
	int		f_len;
	int		pat_len;

	if (filename == NULL || pattern == NULL)
		return (NULL);
	f_len = ft_strlen(filename);
	pat_len = count_patlen(pattern);
	table = ft_calloc(f_len + 1, sizeof(bool *));
	if (table == NULL)
	{
		*flg = true;
		return (NULL);
	}
	i = -1;
	while (++i < f_len + 1)
	{
		table[i] = ft_calloc(pat_len + 1, sizeof(bool));
		if (table[i] == NULL)
		{
			*flg = true;
			return (destroy_table(table, i), NULL);
		}
	}
	return (table);
}

static void	init_table(bool **table, char *filename, char *pattern)
{
	int		i;
	int		height;
	int		width;
	bool	*pat_exp;

	height = ft_strlen(filename);
	width = count_patlen(pattern);
	pat_exp = expand_or_not(pattern);
	if (pat_exp == NULL)
		return ;
	table[0][0] = true;
	i = 0;
	while (++i <= height)
		table[i][0] = false;
	i = 0;
	while (++i <= width)
	{
		if (i == 1 && pat_exp && pattern[i - 1] == '*')
			table[0][i] = true;
		else
			table[0][i] = false;
	}
	free(pat_exp);
}

static void	eval_dp(bool **dp, char *filename, char *pattern)
{
	int	i;
	int	j;
	int	height;
	int	width;
	bool	*pat_exp;

	height = ft_strlen(filename);
	width = count_patlen(pattern);
	pat_exp = expand_or_not(pattern);
	if (pat_exp == NULL)
		return ;
	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			if (pattern[j] == '*' && pat_exp[j])
				dp[i + 1][j + 1] = dp[i][j] | dp[i][j + 1] | dp[i + 1][j];
			else if (filename[i] == pattern[j] && dp[i][j])
				dp[i + 1][j + 1] = true;
		}
	}
	free(pat_exp);
}

bool	matched(char *filename, char *pattern, bool *flg)
{
	int		f_len;
	int		pat_len;
	bool	**table;
	bool	res;

	f_len = ft_strlen(filename);
	pat_len = count_patlen(pattern);
	table = create_table(filename, pattern, flg);
	if (table == NULL)
		return (false);
	init_table(table, filename, pattern);
	eval_dp(table, filename, pattern);
	res = table[f_len][pat_len];
	destroy_table(table, f_len);
	return (res);
}
