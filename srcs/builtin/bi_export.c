/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:11:52 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/28 16:12:14 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// static char	**env_to_declare(t_env *env)
// {
// 	char	**arr;
// 	size_t	i;

// 	arr = (char **)malloc(sizeof(char *) * (env_len(env) + 1));
// 	if (arr == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (env != NULL)
// 	{	
// 		if (env->value == NULL)
// 			arr[i] = ft_strdup(env->key);
// 		else
// 		{
// 			arr[i] = ft_strjoin(env->key, "=");
// 			if (arr[i] == NULL)
// 				return (free2darr(arr), NULL);
// 			arr[i] = ft_strjoin(arr[i], env->value);
// 		}
// 		if (arr[i] == NULL)
// 			return (free2darr(arr), NULL);
// 		env = env->next;
// 		i++;
// 	}
// 	arr[i] = NULL;
// 	return (arr);
// }

// static void	sort_envp(char **envp)
// {
// 	size_t	i;
// 	size_t	j;
// 	char	*tmp;

// 	i = 0;
// 	while (envp[i] != NULL)
// 	{
// 		j = i + 1;
// 		while (envp[j] != NULL)
// 		{
// 			if (ft_strcmp(envp[i], envp[j]) > 0)
// 			{
// 				tmp = envp[i];
// 				envp[i] = envp[j];
// 				envp[j] = tmp;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

// static bool	print_declare(t_env *env)
// {
// 	char	**envp;

// 	envp = env_to_declare(env);
// 	if (envp == NULL)
// 		return (operation_failed("malloc"), false);
// 	sort_envp(envp);
// 	while (*envp != NULL)
// 	{
// 		ft_putstr_fd("declare -x ", STDOUT_FILENO);
// 		ft_putendl_fd(*envp, STDOUT_FILENO);
// 		envp++;
// 	}
// 	return (true);
// }

// static bool	export_variable(t_env *env, char *line)
// {
	// ;
// }

// int	bi_export(t_list *args, t_exec *config)
// {
// 	char	*line;
// 	// bool	declare;

// 	// declare = false;
// 	if (args == NULL)
// 	{
// 		if (!print_declare(config->env))
// 			return (EXIT_KO);
// 		return (EXIT_OK);
// 	}
// 	while (args != NULL)
// 	{
// 		line = args->content;
// 		if (!is_valid_identifier(line))
// 			return (not_a_valid_identifier("export", line), EXIT_KO);
// 		//handle empty variable
// 		if (!export_variable(config->env, line))
// 			return (EXIT_KO);
// 		args = args->next;
// 	}
// 	return (EXIT_OK);
// }
