/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:30:02 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/06 18:30:00 by knishiok         ###   ########.fr       */
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
	free(res_old);
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

	if (res_old == NULL)
	{
		res_old = ft_strdup("");
		if (res_old == NULL)
			return (false);
	}
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

char	*expand_variable_heredoc(char *line, t_env *env)
{
	char	*res;
	char	*new;

	res = NULL;
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

static void	update_quote_expand(char *cur_quote, char c)
{
	if (*cur_quote == '\0')
		*cur_quote = c;
	else if (*cur_quote == c)
		*cur_quote = '\0';
}

bool	expand_variable(char *line, t_env *env, char **expanded)
{
	char	*res;
	char	cur_quote;

	res = NULL;
	cur_quote = '\0';
	while (*line)
	{
		if (ft_strncmp(line, "$\'", 2) == 0 || ft_strncmp(line, "$\"", 2) == 0)
			line++;
		else if (*line == '$' && cur_quote != '\'')
		{
			if (!expand_variable_for_one(&line, env, res, expanded))
				return (free(res),false);
			res = *expanded;
		}
		else
		{
			if (*line == '\'' || *line == '\"')
				update_quote_expand(&cur_quote, *line);
			if (!skip_line(&line, res, expanded))
				return (free(res), false);
			res = *expanded;
		}
	}
	return (true);
}
