/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_into_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 17:35:08 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/28 21:40:11 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static void	set_res(t_list **res, char *line)
{
	char	*str;

	*res = NULL;
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

static t_list	*split_line_to_list(char *line)
{
	t_list	*res;
	t_list	*new;
	char	*word_start;
	char	*chunk;

	set_res(&res, line);
	while (*line)
	{
		if (ft_strchr(" \n\t", *line) == NULL)
		{
			word_start = line;
			while (*line && ft_strchr(" \n\t", *line) == NULL)
				line++;
			chunk = ft_strndup(word_start, line - word_start);
			if (chunk == NULL)
				return (ft_lstclear(&res, free), NULL);
			new = ft_lstnew(chunk);
			if (new == NULL)
				return (ft_lstclear(&res, free), NULL);
			ft_lstadd_back(&res, new);
		}
		else
			line++;
	}
	return (res);
}

static t_list	*expand_variable_to_list(char *line, t_env *env)
{
	t_list	*res;
	char	*expanded;

	expanded = expand_variable(line, env);
	if (expanded == NULL)
		return (NULL);
	res = split_line_to_list(expanded);
	free(expanded);
	if (res == NULL)
		return (operation_failed("malloc"), NULL);
	return (res);
}

static void	rewire_nodes(t_list **orig, t_list **next,
							t_list **head, t_list **tail)
{
	if (*head != NULL)
		(*head)->next = *next;
	else
		*orig = *next;
	while ((*next)->next != NULL)
		*next = (*next)->next;
	(*next)->next = *tail;
}

bool	expand_command_list(t_list **command, t_env *env)
{
	t_list	*orig;
	t_list	*next;
	t_list	*prev;
	t_list	*head;
	t_list	*tail;

	orig = *command;
	prev = NULL;
	while (*command != NULL)
	{
		if (ft_strchr((*command)->content, '$') != NULL)
		{
			head = prev;
			tail = (*command)->next;
			next = expand_variable_to_list((*command)->content, env);
			if (next == NULL)
				return (false);
			rewire_nodes(&orig, &next, &head, &tail);
			*command = next;
		}
		prev = *command;
		*command = (*command)->next;
	}
	*command = orig;
	return (true);
}
