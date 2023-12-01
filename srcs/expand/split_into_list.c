/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_into_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:56:45 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/01 18:15:30 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static void	set_res(t_list **res, char *line)
{
	char	*str;

	*res = NULL;
	if (line == NULL)
		return ;
	if (*line == '\0')
	{
		str = ft_strdup("");
		if (str == NULL)
			return (operation_failed("malloc"));
		*res = ft_lstnew(str);
		if (*res == NULL)
			return (operation_failed("malloc"));
	}
}

static bool	split_line_to_list(char *line, t_list **res)
{
	t_list	*new;
	char	*word_start;
	char	*chunk;

	if (line == NULL)
		return (*res = NULL, true);
	set_res(res, line);
	while (*line)
	{
		if (ft_strchr(" \n\t", *line) == NULL)
		{
			word_start = line;
			while (*line && ft_strchr(" \n\t", *line) == NULL)
				line++;
			chunk = ft_strndup(word_start, line - word_start);
			if (chunk == NULL)
				return (ft_lstclear(res, free), false);
			new = ft_lstnew(chunk);
			if (new == NULL)
				return (ft_lstclear(res, free), false);
			ft_lstadd_back(res, new);
		}
		else
			line++;
	}
	return (true);
}

static bool	expand_variable_to_list(char *line, t_env *env, t_list **res)
{
	char	*expanded;

	if (!expand_variable(line, env, &expanded))
		return (false);
	if (!split_line_to_list(expanded, res))
		return (free(expanded), false);
	free(expanded);
	*res = expand_wildcard(res);
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
