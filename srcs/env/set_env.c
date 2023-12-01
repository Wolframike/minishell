/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:51:27 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/01 17:02:22 by misargsy         ###   ########.fr       */
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
	if (value == NULL)
	{
		new->value = NULL;
		return (new);
	}
	new->value = ft_strdup(value);
	if (new->value == NULL)
		return (free(new->key), free(new), NULL);
	return (new);
}

bool	set_env(t_env **env, char *key, char *value)
{
	t_env	*head;
	t_env	*tmp;

	head = *env;
	while (head != NULL)
	{
		if (ft_strcmp(head->key, key) == 0)
		{
			if (value == NULL)
				return (true);
			free(head->value);
			head->value = ft_strdup(value);
			return (true);
		}
		head = head->next;
	}
	if (head == NULL)
	{
		tmp = create_new_var(key, value);
		if (tmp == NULL)
			return (false);
		add_env_node(env, &tmp);
	}
	return (true);
}
