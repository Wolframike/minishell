/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:07:40 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/29 16:47:21 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static t_env	*create_env_node(char *line)
{
	t_env	*node;
	size_t	i;

	node = (t_env *)malloc(sizeof(t_env));
	if (node == NULL)
		return (NULL);
	ft_bzero(node, sizeof(t_env));
	i = 0;
	while (line[i] != '=' && line[i] != '\0')
		i++;
	node->key = ft_strndup(line, i);
	if (node->key == NULL)
		return (free(node), NULL);
	if (line[i] == '\0')
		node->value = ft_strdup("");
	else
		node->value = ft_strdup(line + i + 1);
	if (node->value == NULL)
		return (free(node->key), free(node), NULL);
	return (node);
}

void	add_env_node(t_env **head, t_env **new)
{
	t_env	*tmp;

	if (*head == NULL)
	{
		*head = *new;
		return ;
	}
	tmp = *head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = *new;
	(*new)->prev = tmp;
}

void	destroy_env_node(t_env *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

void	env_destroy(t_env *env)
{
	t_env	*tmp;

	while (env != NULL)
	{
		tmp = env;
		env = env->next;
		destroy_env_node(tmp);
	}
}

t_env	*env_init(char **envp)
{
	t_env	*env;
	t_env	*new;
	size_t	i;

	i = 0;
	env = NULL;
	if (envp == NULL)
		return (NULL);
	while (envp[i] != NULL)
	{
		new = create_env_node(envp[i]);
		if (new == NULL)
			return (env_destroy(env), NULL);
		add_env_node(&env, &new);
		i++;
	}
	if (!set_env(&env, "?", "0"))
		return (env_destroy(env), NULL);
	return (env);
}
