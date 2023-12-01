/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:19:20 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/01 17:49:11 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	format_single_line(t_env *env, char **line)
{
	if (env->value == NULL)
	{
		*line = ft_strdup(env->key);
		if (*line == NULL)
			return (false);
	}
	else
	{
		*line = ft_strjoin(env->key, "=");
		if (*line == NULL)
			return (false);
		*line = ft_strjoin(*line, env->value);
		if (*line == NULL)
			return (false);
	}
	return (true);
}

char	**env_to_declare(t_env *env)
{
	char	**arr;
	size_t	i;

	arr = (char **)malloc(sizeof(char *) * (env_len(env) + 1));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (env != NULL)
	{
		if (ft_strcmp(env->key, "?") == 0)
		{
			env = env->next;
			continue ;
		}
		if (!format_single_line(env, &arr[i]))
			return (operation_failed("malloc"), free2darr(arr), NULL);
		env = env->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
