/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:45:48 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/23 20:00:15 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execute.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>

int	main(void)
{
	char		*line;
	t_state		data;
	t_ast_node	*node;

	rl_outstream = stderr;
	while (true)
	{
		line = readline("\x1b[31mMINISHELL>>\x1b[0m ");
		if (line == NULL)
			break ;
		node = parse(&data, line);
		execute(node);
		destroy_ast_node(node);
		add_history(line);
		free(line);
	}
	exit(EXIT_SUCCESS);
}
