/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:04:02 by knishiok          #+#    #+#             */
/*   Updated: 2023/12/11 11:31:10 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token	*create_token(char *word, int type)
{
	t_token	*new_token;

	if (word == NULL)
		return (NULL);
	new_token = ft_calloc(1, sizeof(t_token));
	new_token->word = word;
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

static bool	parse_metacharacters(const char **line, t_token **token)
{
	const char	*ops[] = {"&&", "||", "|", "<<", ">>", "<", ">", "(", ")"};
	const int	types[] = {TK_AND, TK_OR, TK_PIPE, TK_HEREDOC,
		TK_APPEND, TK_IN, TK_OUT, TK_LPAREN, TK_RPAREN};
	size_t		i;
	char		*word;

	i = 0;
	while (i < sizeof(ops) / sizeof(*ops))
	{
		if (corresponds(*line, ops[i]))
			break ;
		i++;
	}
	if (i == sizeof(ops) / sizeof(*ops))
		return (true);
	*line += ft_strlen(ops[i]);
	word = ft_strdup(ops[i]);
	if (word == NULL)
		return (false);
	*token = create_token(word, types[i]);
	if (*token == NULL)
		return (free(word), false);
	return (true);
}

static bool	parse_non_metacharacters(const char **line, t_token **token)
{
	const char	*head;
	const char	*tmp;
	char		quote;

	head = *line;
	tmp = *line;
	while (*tmp && !ft_strchr(" \n\t", *tmp) && !is_metacharacter(*tmp))
	{
		if (*tmp == '\'' || *tmp == '\"')
		{
			quote = *tmp++;
			while (*tmp != '\0' && *tmp != quote)
				tmp++;
			if (!*tmp)
				return (*token = NULL, true);
		}
		tmp++;
	}
	*line = tmp;
	*token = create_token(ft_substr(head, 0, tmp - head), TK_WORD);
	if (*token == NULL)
		return (false);
	return (true);
}

static bool	process_character(t_token **t_head, char const **line
								, t_token **cur)
{
	if (is_metacharacter(**line))
	{
		if (!parse_metacharacters(line, &((*cur)->next)))
			return (destroy_token(t_head), operation_failed("malloc"), false);
		if ((*cur)->next == NULL)
			return (destroy_token(t_head),
				ft_putendl_fd("minishell: syntax error", STDERR_FILENO), false);
		*cur = (*cur)->next;
	}
	else if (**line)
	{
		if (!parse_non_metacharacters(line, &((*cur)->next)))
			return (destroy_token(t_head), operation_failed("malloc"), false);
		if ((*cur)->next == NULL)
			return (destroy_token(t_head),
				ft_putendl_fd("minishell: syntax error", STDERR_FILENO), false);
		*cur = (*cur)->next;
	}
	return (true);
}

void	tokenize(t_state *data, const char *line)
{
	t_token	head;
	t_token	*cur;
	t_token	**t_head;

	if (!has_valid_parentheses(line))
	{
		data->token = NULL;
		ft_putendl_fd("minishell: syntax error", STDERR_FILENO);
		return ;
	}
	cur = &head;
	cur->next = NULL;
	t_head = &(cur->next);
	while (*line)
	{
		skip_spaces(&line);
		if (!process_character(t_head, &line, &cur))
			break ;
	}
	data->token = head.next;
}
