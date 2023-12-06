/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:19:20 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/06 21:09:56 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	format_single_line(t_env *env, char **line)
{
	char	*key;

	if (env->value == NULL)
	{
		*line = ft_strdup(env->key);
		if (*line == NULL)
			return (false);
	}
	else
	{
		key = ft_strjoin(env->key, "=");
		if (key == NULL)
			return (false);
		*line = ft_strjoin(key, env->value);
		free(key);
		if (*line == NULL)
			return (false);
	}
	return (true);
}

static char	**env_to_declare(t_env *env)
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

static void	sort_envp(char **envp)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = 0;
	while (envp[i] != NULL)
	{
		j = i + 1;
		while (envp[j] != NULL)
		{
			if (ft_strcmp(envp[i], envp[j]) > 0)
			{
				tmp = envp[i];
				envp[i] = envp[j];
				envp[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_env_with_quotes(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	if (str[i] == '=')
	{
		write(STDOUT_FILENO, str, i + 1);
		ft_putstr_fd("\"", STDOUT_FILENO);
		ft_putstr_fd(str + i + 1, STDOUT_FILENO);
		ft_putendl_fd("\"", STDOUT_FILENO);
	}
	else
		ft_putendl_fd(str, STDOUT_FILENO);
}

bool	print_declare(t_env *env)
{
	char	**envp;
	char	**tmp;

	envp = env_to_declare(env);
	tmp = envp;
	if (envp == NULL)
		return (operation_failed("malloc"), false);
	sort_envp(envp);
	while (*envp != NULL)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		print_env_with_quotes(*envp);
		envp++;
	}
	free2darr(tmp);
	return (true);
}
