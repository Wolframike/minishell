/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:45:48 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/09 20:31:42 by knishiok         ###   ########.fr       */
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
	data->env = config->env;
	data->interrupted = false;
}

static void	terminate(t_state *data, t_exec *config)
{
	char	*exit_code;

	set_term_config(data);
	ft_lstclear(&config->expanded, free);
	exit_code = ft_itoa(config->exit_code);
	if (exit_code == NULL)
	{
		operation_failed("malloc");
		return ;
	}
	if (!set_env(&config->env, "?", exit_code))
		operation_failed("malloc");
	g_signal = 0;
	data->interrupted = false;
	free(exit_code);
}

static void	parse_and_execue(t_state *data, char *line, t_exec *config)
{
	t_ast_node	*node;

	add_history(line);
	set_exec_handler(false);
	node = parse(data, line);
	free(line);
	if (node == NULL)
	{
		if (!set_env(&config->env, "?", "258"))
			operation_failed("malloc");
		g_signal = 0;
		data->interrupted = false;
		return ;
	}
	if (g_signal == SIGINT)
		if (!set_env(&config->env, "?", "1"))
			operation_failed("malloc");
	execute(node, config);
	destroy_ast_node(node);
	terminate(data, config);
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
		line = readline(PROMPT);
		if (line == NULL)
		{
			ft_putendl_fd("exit", STDERR_FILENO);
			break ;
		}
		if (ft_strlen(line) == 0)
		{
			free(line);
			continue ;
		}
		parse_and_execue(&data, line, &config);
	}
	set_term_config(&data);
	exit(config.exit_code);
}
