/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:51:27 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/26 13:02:35 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static t_env	*create_new_var(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	ft_bzero(new, sizeof(t_env));
	new->key = ft_strdup(key);
	if (new->key == NULL)
		return (free(new), NULL);
	new->value = ft_strdup(value);
	if (new->value == NULL)
		return (free(new->key), free(new), NULL);
	return (new);
}

bool	set_env(t_env **env, char *key, char *value)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return (true);
		}
		tmp = tmp->next;
	}
	if (tmp == NULL)
	{
		tmp = create_new_var(key, value);
		if (tmp == NULL)
			return (false);
		add_env_node(env, &tmp);
	}
	return (true);
}
