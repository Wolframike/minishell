/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 02:06:23 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/06 17:05:32 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static bool	access_redir_file(char *filename, t_redir_type type)
{
	bool	permission;

	permission = true;
	if (type == REDIR_IN)
	{
		permission = access(filename, F_OK) == 0;
		if (!permission)
			return (operation_failed(filename), permission);
		permission = access(filename, R_OK) == 0;
		if (!permission)
			return (permission_denied(filename), permission);
	}
	if (type == REDIR_OUT || type == REDIR_APPEND)
	{
		permission = access(filename, F_OK) < 0;
		if (permission)
			return (permission);
		permission = access(filename, W_OK) == 0;
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

static bool	expand_and_check_ambiguous_redirect(char **filename, t_env *env)
{
	t_list	*expanded;
	bool	ambiguous;

	if ((ft_strchr(*filename, '$') != NULL)
		&& (ft_strchr(*filename, '*') != NULL))
		return (true);
	if (!expand_variable_to_list(*filename, env, &expanded))
		return (false);
	ambiguous = (expanded == NULL || (ft_lstsize(expanded) != 1));
	if (ambiguous)
	{
		ft_lstclear(&expanded, free);
		return (ambiguous_redirect(*filename), false);
	}
	free(*filename);
	*filename = ft_strdup(expanded->content);
	ft_lstclear(&expanded, free);
	return (true);
}

bool	set_redir(t_list *redirects, t_env *env)
{
	t_redir	*redir;
	int		fd_tmp;
	bool	status;

	status = true;
	while (redirects != NULL)
	{
		redir = redirects->content;
		if (!expand_and_check_ambiguous_redirect(&redir->filename, env)
			|| !open_redir_file(redir->filename, redir->type, &fd_tmp))
			status = false;
		if (redir->type == REDIR_IN)
			dup2(fd_tmp, STDIN_FILENO);
		else
			dup2(fd_tmp, STDOUT_FILENO);
		redirects = redirects->next;
	}
	return (status);
}

void	only_redir(t_list *redirects, t_env *env, t_exec *config)
{
	t_redir	*redir;
	int		fd_tmp;

	while (redirects != NULL)
	{
		redir = redirects->content;
		if (!expand_and_check_ambiguous_redirect(&redir->filename, env)
			|| !open_redir_file(redir->filename, redir->type, &fd_tmp))
			config->exit_code = EXIT_KO;
		close(fd_tmp);
		redirects = redirects->next;
	}
}
