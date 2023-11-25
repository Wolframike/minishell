/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:58:43 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/21 06:05:51 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_redir	*start_heredoc(char *delimiter)
{
	t_redir	*res;
	int		fd;
	pid_t	pid;
	char	*line;

	res = new_redir(REDIR_HEREDOC, NULL);
	pid = fork();
	if (pid == 0)
	{
		while (true)
		{
			line = readline("> ");
			if (ft_strcmp(line, delimiter) == 0)
			{
				free(line);
				break ;
			}
			ft_putstr_fd(line, fd);
			free(line);
		}
	}
}

t_redir	*parse_heredoc(t_token *token)
{
	int		fd;
	char	*delimiter;

	if (!consume_token(&token, TK_HEREDOC))
		return (NULL);
	delimiter = parse_word(&token);
	if (delimiter == NULL)
		return (NULL);
	fd = open("");
	return (start_heredoc(delimiter));
}
