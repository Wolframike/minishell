/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:06:20 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/26 18:18:00 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_env *env = env_init(envp);
	t_list *lst1;

	char *input1 = ft_strdup("123\'$PWD\'\n\"$HOME\"\n$TERM\n");
	lst1 = expand_variable_list(input1, env);
	free(input1);
	print_command_list(lst1);
	ft_lstclear(&lst1, free);
	env_destroy(env);
}
