/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:30:29 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/15 16:00:36 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/includes/libft.h"

# define SHELL_NAME "minishell"
# define PROMPT "\x1b[34mminishell\x1b[31m|\x1b[34m⇒\x1b[0m "

# define ENOSET 0

void	spit_error(bool is_perror, char *msg);
char	*get_path(char *command, char **envp);

#endif