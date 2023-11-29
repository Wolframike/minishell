/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:58:43 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/29 14:56:47 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execute.h"
#include "expand.h"
#include <readline/readline.h>
#include <fcntl.h>

static char	*get_tmpfile_name(void)
{
	return (ft_strdup("/tmp/.tmpfile"));
}

static void	start_heredoc(char *delimiter, int fd, t_state *data)
{
	pid_t	pid;
	int		status;
	char	*line;
	char	*expanded;

	pid = fork();
	if (pid == 0)
	{
		set_heredoc_child_handler();
		while (true)
		{
			line = readline("> ");
			if (ft_strcmp(line, delimiter) == 0)
			{
				free(line);
				break ;
			}
			expanded = expand_variable_heredoc(line, data->env);
			free(line);
			if (expanded == NULL)
				exit(EXIT_KO);
			ft_putendl_fd(expanded, fd);
		}
		close(fd);
		exit(EXIT_OK);
	}
	waitpid(pid, &status, WUNTRACED);
}

t_redir	*parse_heredoc(t_token **token, t_state *data)
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
	set_heredoc_handler();
	start_heredoc(delimiter, fd, data);
	close(fd);
	free(delimiter);
	if (g_signal == 0)
		return (new_redir(REDIR_IN, filename));
	else
		return (NULL);
}
