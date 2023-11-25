/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:58:43 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/25 18:52:14 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execute.h"
#include <readline/readline.h>
#include <fcntl.h>

static char	*get_tmpfile_name(void)
{
	return (ft_strdup("/tmp/.tmpfile"));
}

static void	start_heredoc(char *delimiter, int fd)
{
	pid_t	pid;
	char	*line;
	int		status;

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
			ft_putendl_fd(line, fd);
			free(line);
		}
		close(fd);
		exit(EXIT_OK);
	}
	while (waitpid(pid, &status, 0) == -1)
		waitpid(pid, &status, 0);
}

t_redir	*parse_heredoc(t_token **token)
{
	int		fd;
	char	*delimiter;
	char	*filename;

	if (!consume_token(token, TK_HEREDOC))
		return (NULL);
	delimiter = parse_word(token);
	if (delimiter == NULL)
		return (NULL);
	filename = get_tmpfile_name();
	if (filename == NULL)
		return (NULL);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, PERMS);
	if (fd == -1)
		return (NULL);
	start_heredoc(delimiter, fd);
	return (new_redir(REDIR_IN, filename));
}
