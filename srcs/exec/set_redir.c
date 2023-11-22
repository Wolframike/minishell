/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 02:06:23 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/22 20:16:56 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static bool	access_redir_file(char *filename, t_redir_type type)
{
	bool	permission;

	if (type == REDIR_IN)
	{
		permission = access(filename, F_OK);
		if (!permission)
			return (operation_failed(filename), permission);
		permission = access(filename, R_OK);
		if (!permission)
			return (permission_denied(filename), permission);
	}
	if (type == REDIR_OUT || type == REDIR_APPEND)
	{
		permission = access(filename, W_OK);
		if (!permission)
			return (permission_denied(filename), permission);
	}
	return (permission);
}

static bool	open_redir_file(char *filename, t_redir_type type, int *fd)
{
	int	fd_tmp;

	if (!access_redir_file(filename, type))
		return (false);
	fd_tmp = -1;
	if (type == REDIR_IN)
		fd_tmp = open(filename, O_RDONLY);
	else if (type == REDIR_OUT)
		fd_tmp = open(filename, O_WRONLY | O_CREAT | O_TRUNC, PERMS);
	else if (type == REDIR_APPEND)
		fd_tmp = open(filename, O_WRONLY | O_CREAT | O_APPEND, PERMS);
	if (fd_tmp == -1)
		return (operation_failed(filename), false);
	*fd = fd_tmp;
	return (true);
}

static void	overwrite_fd(t_redir_type *type, int (*fd)[2], int fd_tmp)
{
	if (*type == REDIR_IN)
	{
		if ((*fd)[0] != STDIN_FILENO)
			close((*fd)[0]);
		(*fd)[0] = fd_tmp;
	}
	else
	{
		if ((*fd)[1] != STDOUT_FILENO)
			close((*fd)[1]);
		(*fd)[1] = fd_tmp;
	}
}

bool	set_redir(t_list *redirects, int (*fd)[2])
{
	t_redir	*redir;
	int		fd_tmp;

	(*fd)[0] = STDIN_FILENO;
	(*fd)[1] = STDOUT_FILENO;
	while (redirects != NULL)
	{
		redir = redirects->content;
		if (!open_redir_file(redir->filename, redir->type, &fd_tmp))
		{
			if ((*fd)[0] != STDIN_FILENO)
				close((*fd)[0]);
			if ((*fd)[1] != STDOUT_FILENO)
				close((*fd)[1]);
			return (false);
		}
		overwrite_fd(&redir->type, fd, fd_tmp);
		redirects = redirects->next;
	}
	return (true);
}
