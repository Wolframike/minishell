/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:45:48 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/28 23:44:13 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execute.h"
#include "env.h"
#include "sig.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>

static void	initialize(t_exec *config, char **envp)
{
	rl_instream = stdin;
	rl_outstream = stdout;
	config->env = env_init(envp);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_exec		config;
	t_state		data;
	t_ast_node	*node;
	int 		fd;

	(void)argc;
	(void)argv;
	initialize(&config, envp);
	data.env = env_init(envp);
	while (true)
	{
		set_idle_handler();
		fd = dup(STDIN_FILENO);
		line = readline("\x1b[31mMINISHELL>>\x1b[0m ");
		if (line == NULL)
		{
			ft_putendl_fd("exit", STDERR_FILENO);
			close(fd);
			break ;
		}
		g_signal = 0;
		set_exec_handler();
		node = parse(&data, line);
		if (node == NULL)
		{
			close(fd);
			continue ;
		}
		execute(node, &config);
		dprintf(STDERR_FILENO, "exit code: %d\n", config.exit_code);
		dprintf(STDERR_FILENO, "fd: %d\n", fd);
		close(fd);
		destroy_ast_node(node);
		add_history(line);
		free(line);
	}
	exit(EXIT_SUCCESS);
}
