/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:11:52 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/05 20:54:04 by misargsy         ###   ########.fr       */
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
	dprintf(STDERR_FILENO, "key: %s\n", key);
	if (key == NULL || (assign && (value == NULL)))
		return (operation_failed("malloc"), false);
	if (!is_valid_identifier(key))
		return (not_a_valid_identifier("export", key), false);
	if (!set_env(&config->env, key, value))
		return (operation_failed("malloc"), false);
	free(key);
	return (true);
}

static bool	process_single_chunk(t_exec *config, char *chunk, size_t *count)
{
	(*count)++;
	if (ft_strcmp(chunk, "export") == 0)
		return (true);
	if (!export_variable(config, chunk))
		return (false);
	return (true);
}

int	bi_export(t_list *args, t_exec *config)
{
	char	*expanded;
	size_t	count;

	count = 0;
	while (args != NULL)
	{
		expanded = expand_variable_export(args->content, config->env);
		if (expanded == NULL)
			return (EXIT_KO);
		if (!process_single_chunk(config, expanded, &count))
			return (free(expanded), EXIT_KO);
		args = args->next;
		free(expanded);
	}
	if (count == 1)
		if (!print_declare(config->env))
			return (EXIT_KO);
	return (EXIT_OK);
}
