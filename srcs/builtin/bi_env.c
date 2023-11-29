/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:30:37 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/29 18:08:47 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	bi_env(t_exec *config)
{
	t_env	*env;

	env = config->env;
	while (env != NULL)
	{
		if (env->value != NULL && ft_strcmp(env->key, "?") != 0)
		{
			ft_putstr_fd(env->key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putendl_fd(env->value, STDOUT_FILENO);
		}
		env = env->next;
	}
	return (EXIT_OK);
}
