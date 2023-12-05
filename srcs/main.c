/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:45:48 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/05 18:13:44 by knishiok         ###   ########.fr       */
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
	char	*shlvl;

	rl_instream = stdin;
	rl_outstream = stderr;
	config->env = env_init(envp);
	data->env = config->env;
	config->exit_code = 0;
	shlvl = get_env(config->env, "SHLVL");
	if (shlvl == NULL)
	{
		set_env(&config->env, "SHLVL", "1");
	}
	else
	{
		shlvl = ft_itoa(ft_atoi(shlvl) + 1);
		if (shlvl == NULL)
		{
			operation_failed("malloc");
			return ;
		}
		set_env(&config->env, "SHLVL", shlvl);
		free(shlvl);
	}
}

static void	terminate(t_exec *config)
{
	char	*exit_code;
	int		fd;

	ft_lstclear(&config->expanded, free);
	exit_code = ft_itoa(config->exit_code);
	if (exit_code == NULL)
	{
		operation_failed("malloc");
		return ;
	}
	set_env(&config->env, "?", exit_code);
	fd = dup(STDOUT_FILENO);
	// dprintf(STDERR_FILENO, "===debug===\nfd: %d\n", fd);
	// dprintf(STDERR_FILENO, "exit_code: %s\n===========\n", exit_code);
	free(exit_code);
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
	printf("%s\n", expand_variable_export("$HOME=\"$PWD\"", data.env));
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
		set_exec_handler(false);
		node = parse(&data, line);
		if (node == NULL)
		{
			set_env(&(data.env), "?", "1");
			continue ;
		}
		execute(node, &config);
		terminate(&config);
		destroy_ast_node(node);
		add_history(line);
		free(line);
	}
	exit(config.exit_code);
}
