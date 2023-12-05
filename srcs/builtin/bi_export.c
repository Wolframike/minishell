/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:11:52 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/01 20:00:47 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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

static bool	print_declare(t_env *env)
{
	char	**envp;

	envp = env_to_declare(env);
	if (envp == NULL)
		return (operation_failed("malloc"), false);
	sort_envp(envp);
	while (*envp != NULL)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(*envp, STDOUT_FILENO);
		envp++;
	}
	return (true);
}

static bool	export_variable(t_exec *config, char *line)
{
	char	*key;
	char	*value;
	bool	assign;

	assign = ft_strchr(line, '=') != NULL;
	if (assign)
	{
		key = ft_substr(line, 0, ft_strchr(line, '=') - line);
		value = ft_strchr(line, '=') + 1;
	}
	else
	{
		key = ft_strdup(line);
		value = NULL;
	}
	if (key == NULL || (assign && (value == NULL)))
		return (operation_failed("malloc"), false);
	if (!set_env(&config->env, key, value))
		return (operation_failed("malloc"), false);
	free(key);
	return (true);
}

int	bi_export(t_list *args, t_exec *config)
{
	char	*line;

	if (args->next == NULL)
	{
		if (!print_declare(config->env))
			return (EXIT_KO);
		return (EXIT_OK);
	}
	while (args != NULL)
	{
		line = args->content;
		if (!is_valid_identifier(line))
			return (not_a_valid_identifier("export", line), EXIT_KO);
		if (!export_variable(config, line))
			return (EXIT_KO);
		args = args->next;
	}
	return (EXIT_OK);
}
