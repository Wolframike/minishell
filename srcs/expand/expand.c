/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 13:40:29 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/29 15:55:01 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static char	*get_variable_name(char **line)
{
	char	*res;
	int		len;

	if (**line != '$')
		return (NULL);
	(*line)++;
	len = 0;
	if (**line == '?')
	{
		res = ft_strdup("?");
		len++;
	}
	else if (!ft_isalpha(**line) && **line != '_')
		res = ft_strdup("$");
	else
	{
		while (ft_isalnum(*(*line + len)) || *(*line + len) == '_')
			len++;
		res = ft_substr(*line, 0, len);
	}
	if (res == NULL)
		return (operation_failed("malloc"), NULL);
	(*line) += len;
	return (res);
}

static char	*expand_variable_for_one(char **line, t_env *env, char *res_old)
{
	char	*res;
	char	*value;
	char	*varname;

	varname = get_variable_name(line);
	if (varname == NULL)
		return (NULL);
	value = get_env(env, varname);
	if (ft_strcmp(varname, "$") == 0)
		value = "$";
	free(varname);
	if (value == NULL)
		value = "";
	value = ft_strdup(value);
	if (value == NULL)
		return (operation_failed("malloc"), NULL);
	res = ft_strjoin(res_old, value);
	free(res_old);
	free(value);
	if (res == NULL)
		return (operation_failed("malloc"), NULL);
	return (res);
}

static char	*proceed_line(char **line, char *res_old)
{
	int		i;
	int		src_len;
	char	*res;

	src_len = ft_strlen(res_old);
	res = ft_calloc(src_len + 2, sizeof(char));
	if (res == NULL)
		return (operation_failed("malloc"), NULL);
	i = -1;
	while (++i < src_len)
		res[i] = res_old[i];
	free(res_old);
	res[src_len] = **line;
	(*line)++;
	return (res);
}

static void	update_flag(bool *is_single_quote, char **line)
{
	if (**line == '\'')
		*is_single_quote = !(*is_single_quote);
	(*line)++;
}

char	*expand_variable_heredoc(char *line, t_env *env)
{
	char	*res;

	res = ft_strdup("");
	if (res == NULL)
		return (operation_failed("malloc"), NULL);
	while (*line)
	{
		if (*line == '$')
		{
			res = expand_variable_for_one(&line, env, res);
			if (res == NULL)
				return (NULL);
		}
		else
		{
			res = proceed_line(&line, res);
			if (res == NULL)
				return (NULL);
		}
	}
	return (res);	
}

char	*expand_variable(char *line, t_env *env)
{
	char	*res;
	bool	is_single_quote;

	res = ft_strdup("");
	if (res == NULL)
		return (operation_failed("malloc"), NULL);
	// if (ft_strcmp(line, "") == 0)
	// 	return (res);
	is_single_quote = false;
	while (*line)
	{
		if (*line == '$' && is_single_quote == false)
		{
			res = expand_variable_for_one(&line, env, res);
			if (res == NULL)
				return (NULL);
		}
		else if (*line == '\'' || *line == '\"')
			update_flag(&is_single_quote, &line);
		else
		{
			res = proceed_line(&line, res);
			if (res == NULL)
				return (NULL);
		}
	}
	// if (ft_strcmp(res, "") == 0)
	// 	return (free(res), NULL);
	return (res);
}
