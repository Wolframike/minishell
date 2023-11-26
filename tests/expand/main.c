/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:06:20 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/26 19:03:04 by knishiok         ###   ########.fr       */
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

	// char *input1 = ft_strdup("$A$A$A$A");
	char	input1[1000] = "cd $HOME";
	printf("String to parse: %s\n", input1);
	lst1 = expand_variable_list(input1, env);
	// free(input1);
	print_command_list(lst1);
	ft_lstclear(&lst1, free);
	env_destroy(env);
}
