/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 08:05:05 by misargsy          #+#    #+#             */
/*   Updated: 2023/10/12 01:21:03 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef FDMAX
#  define FDMAX 24576
# endif

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>

char	*gnl_strjoin(char *s1, const char *s2);
char	*get_next_line(int fd);
int		gnl_reader_terminator(char **buffer, char **line);
char	*gnl_reader_wrapper(int fd, char **buffer);
int		gnl_reader(int fd, char **buffer, char **line);
void	gnl_formatter(char **buffer, char **line);

#endif