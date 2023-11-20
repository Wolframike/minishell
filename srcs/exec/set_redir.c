/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 02:06:23 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/21 03:00:54 by misargsy         ###   ########.fr       */
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
	if (type == REDIR_IN)
		fd_tmp = open(filename, O_RDONLY);
	else if (type == REDIR_OUT)
		fd_tmp = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == REDIR_APPEND)
		fd_tmp = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_tmp == -1)
		return (operation_failed(filename), false);
	*fd = fd_tmp;
	return (true);
}

void	set_redir(t_ast_node *node, int *fd[2])
{
	t_redir	*redir;
	int		fd_tmp;

	(*fd)[0] = STDIN_FILENO;
	(*fd)[1] = STDOUT_FILENO;
	while (node->redir != NULL)
	{
		redir = node->redir->content;
		if (!open_redir_file(redir->filename, redir->type, &fd_tmp))
			return ;
		if (node->redir->next != NULL)
			close(fd_tmp);
		else
		{
			if (redir->type == REDIR_IN)
				(*fd)[0] = fd_tmp;
			else
				(*fd)[1] = fd_tmp;
		}
		node->redir = node->redir->next;
	}
}
