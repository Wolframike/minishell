/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:08:01 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/29 16:50:55 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static size_t	env_len(t_env *env)
{
	size_t	len;

	len = 0;
	while (env != NULL)
	{
		len++;
		env = env->next;
	}
	return (len);
}

char	**env_to_array(t_env *env)
{
	char	**arr;
	size_t	i;

	arr = (char **)malloc(sizeof(char *) * (env_len(env) + 1));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (env != NULL && env->value != NULL)
	{
		if (ft_strcmp(env->key, "?") == 0)
		{
			env = env->next;
			continue ;
		}
		arr[i] = ft_strjoin(env->key, "=");
		if (arr[i] == NULL)
			return (free2darr(arr), NULL);
		arr[i] = ft_strjoin(arr[i], env->value);
		if (arr[i] == NULL)
			return (free2darr(arr), NULL);
		env = env->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

void	unset_env(t_env **env, char *key)
{
	t_env	*prev;
	t_env	*next;
	t_env	*tmp;
	size_t	i;

	tmp = *env;
	i = 0;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			prev = tmp->prev;
			next = tmp->next;
			if (prev != NULL)
				prev->next = next;
			if (next != NULL)
				next->prev = prev;
			destroy_env_node(tmp);
			if (i == 0)
				*env = next;
			return ;
		}
		i++;
		tmp = tmp->next;
	}
}

char	*get_env(t_env *env, char *key)
{
	while (env != NULL)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
