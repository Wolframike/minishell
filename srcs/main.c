/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:45:48 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/29 16:48:33 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execute.h"
#include "env.h"
#include "sig.h"
#include "termconf.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>

static void	initialize(t_exec *config, t_state *data, char **envp)
{
	rl_instream = stdin;
	rl_outstream = stdout;
	config->env = env_init(envp);
	data->env = config->env;
	config->exit_code = 0;
}

static void	terminate(t_exec *config)
{
	char	*exit_code;

	exit_code = ft_itoa(config->exit_code);
	dprintf(STDERR_FILENO, "exit_code: %s\n", exit_code);
	if (exit_code == NULL)
	{
		operation_failed("malloc");
		return ;
	}
	set_env(&config->env, "?", exit_code);
	free(exit_code);
	int fd = dup(STDOUT_FILENO);
	dprintf(STDERR_FILENO, "===debug===\nfd: %d\n===========n", fd);
	close(fd);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_exec		config;
	t_state		data;
	t_ast_node	*node;

	(void)argc;
	(void)argv;
	initialize(&config, &data, envp);
	while (true)
	{
		set_idle_handler();
		line = readline("\x1b[31mMINISHELL>>\x1b[0m ");
		if (line == NULL)
		{
			ft_putendl_fd("exit", STDERR_FILENO);
			break ;
		}
		g_signal = 0;
		set_exec_handler();
		node = parse(&data, line);
		if (node == NULL)
			continue ;
		execute(node, &config);
		terminate(&config);
		destroy_ast_node(node);
		add_history(line);
		free(line);
	}
	free(data.termconf);
	exit(EXIT_SUCCESS);
}
