/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_io_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:11:26 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/25 18:16:34 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_redir	*parse_io_file_helper(t_token **token)
{
	t_redir_type	type;
	char			*filename;

	if ((*token)->type == TK_IN)
		type = REDIR_IN;
	else if ((*token)->type == TK_OUT)
		type = REDIR_OUT;
	else if ((*token)->type == TK_APPEND)
		type = REDIR_APPEND;
	else
		return (NULL);
	*token = (*token)->next;
	filename = parse_word(token);
	if (filename == NULL)
		return (NULL);
	return (new_redir(type, filename));
}

t_list	*parse_io_file(t_token **token)
{
	t_list	*res;
	t_redir	*redir;

	if ((*token)->type == TK_HEREDOC)
		redir = parse_heredoc(token);
	else if (is_redir(*token))
		redir = parse_io_file_helper(token);
	else
		return (NULL);
	res = ft_lstnew(redir);
	if (res == NULL)
		return (NULL);
	return (res);
}

t_list	*parse_io_files(t_token **token)
{
	t_list	*res;
	t_list	*redir;

	res = NULL;
	while (is_redir(*token))
	{
		redir = parse_io_file(token);
		if (redir == NULL)
		{
			ft_lstclear(&res, free);
			return (NULL);
		}
		ft_lstadd_back(&res, redir);
	}
	return (res);
}
