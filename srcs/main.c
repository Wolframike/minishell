/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:45:48 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/26 18:34:31 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execute.h"
#include "env.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>

int	main(void)
{
	char		*line;
	t_state		data;
	t_ast_node	*node;

	rl_outstream = stderr;
	data.env = env_init(environ);
	while (true)
	{
		line = readline("\x1b[31mMINISHELL>>\x1b[0m ");
		if (line == NULL)
			break ;
		node = parse(&data, line);
		if (node == NULL)
			continue ;
		//print_node(node);
		execute(node);
		destroy_ast_node(node);
		add_history(line);
		free(line);
	}
	exit(EXIT_SUCCESS);
}
