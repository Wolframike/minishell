/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:30:02 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/11 01:50:59 by knishiok         ###   ########.fr       */
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
		char **res)
{
	char	*value;
	char	*varname;
	char	*res_old;

	if (!strdup_case_null(&res_old, *res))
		return (operation_failed("malloc"), false);
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
	free(*res);
	*res = ft_strjoin(res_old, value);
	if (res == NULL)
		return (operation_failed("malloc"), free(value), free(res_old), false);
	return (free(value), free(res_old), true);
}

char	*expand_variable_heredoc(char *line, t_env *env)
{
	char	*res;

	res = NULL;
	while (*line)
	{
		if (*line == '$')
		{
			if (!expand_variable_for_one(&line, env, &res))
				return (NULL);
		}
		else
		{
			if (!skip_line(&line, &res))
				return (NULL);
		}
	}
	return (res);
}

static void	update_quote_expand(char *cur_quote, char c)
{
	if (*cur_quote == '\0')
		*cur_quote = c;
	else if (*cur_quote == c)
		*cur_quote = '\0';
}

bool	expand_variable(char *line, t_env *env, char **expanded)
{
	char	cur_quote;

	cur_quote = '\0';
	while (*line)
	{
		if (cur_quote == '\0' && (ft_strncmp(line, "$\'", 2) == 0
				|| ft_strncmp(line, "$\"", 2) == 0))
			line++;
		else if (*line == '$' && cur_quote != '\'')
		{
			if (!expand_variable_for_one(&line, env, expanded))
				return (false);
		}
		else
		{
			if (*line == '\'' || *line == '\"')
				update_quote_expand(&cur_quote, *line);
			if (!skip_line(&line, expanded))
				return (false);
		}
	}
	return (true);
}
