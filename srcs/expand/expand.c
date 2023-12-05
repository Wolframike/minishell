/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:30:02 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/05 20:17:25 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static bool	get_variable_name(char **line, char **varname)
{
	int		len;

	if (**line != '$')
		return (NULL);
	(*line)++;
	len = 0;
	if (**line == '?')
	{
		*varname = ft_strdup("?");
		len++;
	}
	else if (!ft_isalpha(**line) && **line != '_')
		*varname = ft_strdup("$");
	else
	{
		while (ft_isalnum(*(*line + len)) || *(*line + len) == '_')
			len++;
		*varname = ft_substr(*line, 0, len);
	}
	if (*varname == NULL)
		return (operation_failed("malloc"), false);
	(*line) += len;
	return (true);
}

static bool	expand_variable_for_one(char **line, t_env *env,
		char *res_old, char **res_new)
{
	char	*res;
	char	*value;
	char	*varname;

	if (!get_variable_name(line, &varname))
		return (free(res_old), false);
	value = get_env(env, varname);
	if (ft_strcmp(varname, "$") == 0)
		value = "$";
	free(varname);
	if (value == NULL)
		value = "";
	value = ft_strdup(value);
	if (value == NULL)
		return (operation_failed("malloc"), free(res_old), false);
	res = ft_strjoin(res_old, value);
	free(value);
	if (res == NULL)
		return (operation_failed("malloc"), free(res_old), false);
	*res_new = res;
	return (true);
}

bool	skip_line(char **line, char *res_old, char **res)
{
	int		i;
	int		src_len;

	src_len = ft_strlen(res_old);
	*res = ft_calloc(src_len + 2, sizeof(char));
	if (*res == NULL)
	{
		free(res_old);
		return (operation_failed("malloc"), false);
	}
	i = -1;
	while (++i < src_len)
		(*res)[i] = res_old[i];
	(*res)[src_len] = **line;
	free(res_old);
	(*line)++;
	return (true);
}

static void	update_flag(bool *is_single_quote, char **line)
{
	if (**line == '\'')
		*is_single_quote = !(*is_single_quote);
}

char	*expand_variable_heredoc(char *line, t_env *env)
{
	char	*res;
	char	*new;

	res = ft_strdup("");
	if (res == NULL)
		return (operation_failed("malloc"), NULL);
	while (*line)
	{
		if (*line == '$')
		{
			if (!expand_variable_for_one(&line, env, res, &new))
				return (NULL);
			res = new;
		}
		else
		{
			if (!skip_line(&line, res, &new))
				return (NULL);
			res = new;
		}
	}
	return (res);
}

bool	expand_variable(char *line, t_env *env, char **expanded)
{
	char	*res;
	bool	is_single_quote;

	res = ft_strdup("");
	if (res == NULL)
		return (operation_failed("malloc"), NULL);
	is_single_quote = false;
	while (*line)
	{
		if (*line == '$' && is_single_quote == false)
		{
			if (!expand_variable_for_one(&line, env, res, expanded))
				return (false);
			res = *expanded;
		}
		else
		{
			if (*line == '\'' || *line == '\"')
				update_flag(&is_single_quote, &line);
			if (!skip_line(&line, res, expanded))
				return (false);
			res = *expanded;
		}
	}
	return (true);
}
