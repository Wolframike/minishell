/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:45:48 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/05 23:23:54 by misargsy         ###   ########.fr       */
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

static void	init_config(t_exec *config, char **envp)
{
	char	*shlvl;

	ft_bzero(config, sizeof(t_exec));
	config->cwd = getcwd(NULL, 0);
	if (config->cwd == NULL)
		error_retrieving_cd("shell-init");
	config->env = env_init(envp);
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

static void	initialize(t_exec *config, t_state *data, char **envp)
{
	rl_instream = stdin;
	rl_outstream = stderr;
	init_config(config, envp);
	set_term_config(data, 0);
	data->env = config->env;
}

static void	terminate(t_exec *config)
{
	char	*exit_code;

	ft_lstclear(&config->expanded, free);
	exit_code = ft_itoa(config->exit_code);
	if (exit_code == NULL)
	{
		operation_failed("malloc");
		return ;
	}
	set_env(&config->env, "?", exit_code);
	// int fd = dup(STDOUT_FILENO);
	// dprintf(STDERR_FILENO, "===debug===\nfd: %d\n", fd);
	// dprintf(STDERR_FILENO, "exit_code: %s\n===========\n", exit_code);
	// close(fd);
	free(exit_code);
}

static bool	parse_and_execue(t_state *data, char **line, t_exec *config)
{
	t_ast_node	*node;

	g_signal = 0;
	set_exec_handler(false);
	node = parse(data, *line);
	if (node == NULL)
	{
		set_env(&(data->env), "?", "1");
		free(*line);
		return (false);
	}
	execute(node, config);
	destroy_ast_node(node);
	free(*line);
	return (true);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_exec		config;
	t_state		data;

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
		add_history(line);
		if (!parse_and_execue(&data, &line, &config))
			continue ;
		terminate(&config);
		set_term_config(&data, 1);
	}
	set_term_config(&data, 1);
	exit(config.exit_code);
}
