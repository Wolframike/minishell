/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:45:48 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/08 18:54:28 by knishiok         ###   ########.fr       */
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

	ft_lstclear(&config->expanded, free);
	exit_code = ft_itoa(config->exit_code);
	if (exit_code == NULL)
	{
		operation_failed("malloc");
		return ;
	}
	set_env(&config->env, "?", exit_code);
	g_signal = 0;
	data->interrupted = false;
	free(exit_code);
}

void	print_command_list(t_list *list)
{
	if (list == NULL)
	{
		puts("(null)");
		puts("==========================");
		return ;
	}
	printf("%s->", list->content);
	print_command_list(list->next);
}

void	print_redir_list(t_list *list)
{
	t_redir	*redir;

	if (list == NULL || list->content == NULL)
	{
		puts("(null)");
		puts("==========================");
		return ;
	}
	redir = (t_redir *)list->content;
	printf("Redirection type: %d\n", redir->type);
	if (redir->filename == NULL)
		return ;
	printf("Redirection filename: %s\n", redir->filename);
	print_redir_list(list->next);
}

void	print_node(t_ast_node *node)
{
	if (node == NULL)
	{
		printf("(null)\n");
		puts("==========================");
		return ;
	}
	printf("ast node type: %d\n", node->type);
	if (node->command != NULL)
	{
		printf("Command list: ");
		print_command_list(node->command);
	}
	if (node->redir != NULL)
	{
		printf("Redirection list: ");
		print_redir_list(node->redir);
	}
	puts("==========================");
	printf("Left node: \n");
	print_node(node->left);
	printf("Right node\n");
	print_node(node->right);
}

static bool	parse_and_execue(t_state *data, char **line, t_exec *config)
{
	t_ast_node	*node;

	set_exec_handler(false);
	node = parse(data, *line);
	if (node == NULL)
	{
		set_env(&(data->env), "?", "258");
		free(*line);
		return (false);
	}
	print_node(node);
	if (g_signal == SIGINT)
	{
		set_env(&config->env, "?", "1");
		config->exit_code = 1;
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
		line = readline(PROMPT);
		if (line == NULL)
		{
			ft_putendl_fd("exit", STDERR_FILENO);
			break ;
		}
		if (ft_strlen(line) > 0)
			add_history(line);
		if (!parse_and_execue(&data, &line, &config))
			continue ;
		terminate(&data, &config);
		set_term_config(&data);
	}
	set_term_config(&data);
	exit(config.exit_code);
}
