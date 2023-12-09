/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_into_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:56:45 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/09 21:21:47 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static bool	split_line_to_list(char *line, t_list **res)
{
	*res = NULL;
	if (line == NULL)
		return (true);
	while (*line)
	{
		if (!handle_quote(res, &line))
			return (false);
		if (*line == '\0')
			break ;
		if (ft_strchr(" \n\t", *line) != NULL)
			line++;
	}
	return (true);
}

bool	expand_variable_export(char *line, t_env *env, char **expanded)
{
	char	*str_quote;
	char	*head;

	if (!expand_variable(line, env, &str_quote))
		return (NULL);
	*expanded = ft_strdup("");
	if (*expanded == NULL)
		return (false);
	head = str_quote;
	while (*str_quote)
	{
		if (*str_quote == '\'' || *str_quote == '\"')
			str_quote++;
		else
		{
			if (!skip_line(&str_quote, *expanded, expanded))
				return (free(*expanded), false);
		}
	}
	free(head);
	return (true);
}

bool	expand_variable_to_list(char *line, t_env *env, t_list **res)
{
	char	*expanded;

	if (!expand_variable(line, env, &expanded))
		return (false);
	if (!split_line_to_list(expanded, res))
		return (free(expanded), false);
	free(expanded);
	*res = expand_wildcard(res);
	if (!remove_quotes_list(res))
		return (ft_lstclear(res, free), false);
	return (true);
}

bool	expand_command_list(t_list *command, t_env *env, t_list **head)
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
