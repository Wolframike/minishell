/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_into_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:56:45 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/05 09:49:44 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static bool	handle_quote(t_list **res, char **line)
{
	char	*word_start;
	char	*chunk;
	t_list	*new;

	word_start = *line;
	(*line)++;
	while (**line && ft_strchr("\'\"", **line) == NULL)
		(*line)++;
	if (**line != '\0')
		(*line)++;
	chunk = ft_strndup(word_start, *line - word_start);
	if (chunk == NULL)
		return (ft_lstclear(res, free), false);
	new = ft_lstnew(chunk);
	if (new == NULL)
		return (ft_lstclear(res, free), false);
	ft_lstadd_back(res, new);
	return (true);
}

static bool	split_line_to_list(char *line, t_list **res)
{
	t_list	*new;
	char	*word_start;
	char	*chunk;

	*res = NULL;
	if (line == NULL)
		return (true);
	while (*line)
	{
		if ((*line == '\"' || *line == '\'') && !handle_quote(res, &line))
			return (false);
		else if (*line == '\0')
			break ;
		else if (ft_strchr(" \n\t", *line) == NULL)
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

// void print_list(t_list *lst)
// {
// 	while (lst)
// 	{
// 		printf("content: |%s|\n", lst->content);
// 		lst = lst->next;
// 	}
// }

static t_list	*remove_quotes(char *line)
{
	t_list	*res;
	char	*res_str;

	res_str = ft_strdup("");
	while (*line)
	{
		if (*line == '\'' || *line == '\"')
			line++;
		else
		{
			if (!skip_line(&line, res_str, &res_str))
				return (free(res_str), NULL);
		}
	}
	res = ft_lstnew(res_str);
	if (res == NULL)
		return (free(res_str), NULL);
	return (res);
}

static bool	remove_quotes_list(t_list **res_old)
{
	t_list	*head;
	t_list	*res;
	t_list	*new;
	t_list	*tmp;

	res = NULL;
	head = *res_old;
	tmp = *res_old;
	while (tmp)
	{
		new = remove_quotes(tmp->content);
		if (new == NULL)
			return (ft_lstclear(&res, free), false);
		ft_lstadd_back(&res, new);
		tmp = tmp->next;
	}
	ft_lstclear(&head, free);
	*res_old = res;
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
