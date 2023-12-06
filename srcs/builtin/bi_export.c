/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:11:52 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/06 21:03:10 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static char	*join_all_args(t_list *args)
{
	char	*res;
	char	*tmp;

	res = ft_strdup("");
	if (res == NULL)
		return (NULL);
	while (args != NULL)
	{
		tmp = res;
		res = ft_strjoin(res, args->content);
		free(tmp);
		if (res == NULL)
			return (NULL);
		args = args->next;
		if (args != NULL)
		{
			tmp = res;
			res = ft_strjoin(res, " ");
			free(tmp);
			if (res == NULL)
				return (NULL);
		}
	}
	return (res);
}

static bool	get_single_arg(char **line, char **arg)
{
	ssize_t	i;
	bool	squote;
	bool	dquote;

	i = 0;
	squote = false;
	dquote = false;
	while ((*line)[i] != '\0')
	{
		if ((*line)[i] == '\"')
			dquote = !dquote;
		if ((*line)[i] == '\'')
			squote = !squote;
		if ((*line)[i] == ' ' && !squote && !dquote)
		{
			*arg = ft_substr(*line, 0, i);
			*line += i + 1;
			return (*arg != NULL);
		}
		i++;
	}
	*arg = ft_strdup(*line);
	*line += i;
	return (*arg != NULL);
}

static bool	export_variable(t_exec *config, char *line)
{
	char	*key;
	char	*value;
	bool	assign;

	assign = ft_strchr(line, '=') != NULL;
	if (assign)
		key = ft_substr(line, 0, ft_strchr(line, '=') - line);
	else
		key = ft_strdup(line);
	if (assign)
		value = ft_strchr(line, '=') + 1;
	else
		value = NULL;
	if (key == NULL || (assign && (value == NULL)))
		return (operation_failed("malloc"), false);
	if (!is_valid_identifier(key))
		return (not_a_valid_identifier("export", key), false);
	if (!set_env(&config->env, key, value))
		return (operation_failed("malloc"), false);
	return (free(key), true);
}

static bool	process_args(char **line, t_exec *config, bool *declare)
{
	char	*arg;

	while (**line != '\0')
	{
		arg = NULL;
		if (!get_single_arg(line, &arg))
			return (false);
		if (arg == NULL)
			return (true);
		if (ft_strcmp(arg, "export") == 0)
		{
			free(arg);
			continue ;
		}
		*declare = false;
		if (!export_variable(config, arg))
			return (free(arg), false);
		free(arg);
	}
	return (true);
}

int	bi_export(t_list *args, t_exec *config)
{
	char	*line;
	char	*tmp;
	bool	declare;

	line = join_all_args(args);
	if (line == NULL)
		return (operation_failed("malloc"), EXIT_KO);
	tmp = line;
	declare = true;
	if (!process_args(&line, config, &declare))
		return (free(tmp), EXIT_KO);
	if (declare)
		if (!print_declare(config->env))
			return (operation_failed("malloc"), free(line), EXIT_KO);
	free(tmp);
	return (EXIT_OK);
}
