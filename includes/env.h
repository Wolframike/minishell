/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 11:59:58 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/29 16:46:49 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "libft.h"
# include "utils.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

t_env	*env_init(char **envp);
void	add_env_node(t_env **head, t_env **new);

void	env_destroy(t_env *env);

void	destroy_env_node(t_env *env);

char	**env_to_array(t_env *env);
void	unset_env(t_env **env, char *key);
bool	set_env(t_env **env, char *key, char *value);
char	*get_env(t_env *env, char *key);

#endif
