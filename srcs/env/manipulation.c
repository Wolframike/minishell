/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:08:01 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/26 12:51:12 by misargsy         ###   ########.fr       */
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
	while (env != NULL)
	{
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
	t_env	*tmp;

	tmp = *env;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (tmp->prev == NULL)
				*env = tmp->next;
			else
				tmp->prev->next = tmp->next;
			if (tmp->next != NULL)
				tmp->next->prev = tmp->prev;
			destroy_env_node(tmp);
			return ;
		}
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
