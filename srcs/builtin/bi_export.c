/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:11:52 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/11 02:35:21 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	export_variable(t_exec *config, char *line)
{
	char	*key;
	char	*value;
	bool	assign;

	assign = ft_strchr(line, '=') != NULL;
	if (assign)
		key = ft_substr(line, 0, ft_strchr(line, '=') - line);
	else
		key = ft_strdup(line);
	if (assign)
		value = ft_strchr(line, '=') + 1;
	else
		value = NULL;
	if (key == NULL || (assign && (value == NULL)))
		return (operation_failed("malloc"), false);
	if (!is_valid_identifier(key))
		return (not_a_valid_identifier("export", line), free(key), false);
	if (!set_env(&config->env, key, value))
		return (operation_failed("malloc"), free(key), false);
	return (free(key), true);
}

static bool	expand_command_list_export(t_list *command,
	t_env *env, t_list **head)
{
	t_list	*new;
	t_list	*orig;

	orig = command;
	*head = NULL;
	while (command != NULL)
	{
		if (!expand_variable_to_list(command->content, env, &new))
			return (ft_lstclear(&orig, free), false);
		ft_lstadd_back(head, new);
		command = command->next;
	}
	return (true);
}

int	bi_export(t_list *args, t_exec *config)
{
	t_list	*head;
	t_list	*orig;

	if (!expand_command_list_export(args, config->env, &head))
		return (EXIT_KO);
	orig = head;
	head = head->next;
	if (head == NULL)
	{
		ft_lstclear(&orig, free);
		if (!print_declare(config->env))
			return (operation_failed("malloc"), EXIT_KO);
		return (EXIT_OK);
	}
	while (head != NULL)
	{
		export_variable(config, head->content);
		head = head->next;
	}
	ft_lstclear(&orig, free);
	return (EXIT_OK);
}
