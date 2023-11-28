/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:45:48 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/28 22:17:59 by knishiok         ###   ########.fr       */
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
	int			fd;

	(void)argc;
	(void)argv;
	initialize(&config, envp);
	set_term_config(&data, 0);
	data.env = env_init(envp);
	while (true)
	{
		set_idle_handler();
		fd = dup(STDIN_FILENO);
		printf("%d\n", fd);
		close(fd);
		line = readline("\x1b[31mMINISHELL>>\x1b[0m ");
		if (line == NULL)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		g_signal = 0;
		set_exec_handler();
		set_term_config(&data, 1);
		node = parse(&data, line);
		if (node == NULL)
			continue ;
		// print_node(node);
		set_term_config(&data, 1);
		// reset(&config);
		execute(node, &config);
		dprintf(STDERR_FILENO, "exit code: %d\n", config.exit_code);
		destroy_ast_node(node);
		add_history(line);
		free(line);
	}
	free(data.termconf);
	exit(EXIT_SUCCESS);
}
