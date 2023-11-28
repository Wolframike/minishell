/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:45:48 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/28 17:19:55 by misargsy         ###   ########.fr       */
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

static void	reset(t_exec *config)
{
	config->exit_code = EXIT_OK;
	config->fork_count = 0;
}

static void	wait_all(t_exec config)
{
	while (config.fork_count > 0)
	{
		wait(NULL);
		config.fork_count--;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_exec		config;
	t_state		data;
	t_ast_node	*node;

	(void)argc;
	(void)argv;
	initialize(&config, envp);
	data.env = env_init(envp);
	while (true)
	{
		set_idle_handler();
		line = readline("\x1b[31mMINISHELL>>\x1b[0m ");
		if (line == NULL)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		g_signal = 0;
		set_exec_handler();
		node = parse(&data, line);
		if (node == NULL)
			continue ;
		reset(&config);
		execute(node, &config);
		wait_all(config);
		destroy_ast_node(node);
		add_history(line);
		free(line);
	}
	exit(EXIT_SUCCESS);
}
