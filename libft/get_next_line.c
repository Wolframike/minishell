/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 10:38:28 by knishiok          #+#    #+#             */
/*   Updated: 2023/10/29 13:51:50 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*strjoin_with_free(char *buf, char *tmp)
{
	char	*res;

	res = ft_strjoin(buf, tmp);
	free(buf);
	return (res);
}

char	*read_file(int fd, char *buf)
{
	int		read_bytes;
	char	*tmp;

	read_bytes = 1;
	tmp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (tmp == NULL)
		return (NULL);
	while (read_bytes > 0 && ft_strchr(buf, '\n') == NULL)
	{
		read_bytes = read(fd, tmp, BUFFER_SIZE);
		if (read_bytes < 0)
		{
			free(tmp);
			return (NULL);
		}
		tmp[read_bytes] = '\0';
		buf = strjoin_with_free(buf, tmp);
	}
	free(tmp);
	return (buf);
}

char	*get_line(char *buf)
{
	int		i;
	char	*res;

	if (buf == NULL || buf[0] == '\0')
		return (NULL);
	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	res = ft_calloc(i + 1, sizeof(char));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (buf[i] && buf[i] != '\n')
	{
		res[i] = buf[i];
		i++;
	}
	if (buf[i] == '\n')
		res[i] = '\n';
	return (res);
}

char	*slide_str(char *str)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	res = ft_calloc(ft_strlen(str) - i++ + 1, sizeof(char));
	if (res == NULL)
		return (NULL);
	j = 0;
	while (str[i])
		res[j++] = str[i++];
	free(str);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffer[FD_MAX];
	char		*res;

	if (fd < 0 || BUFFER_SIZE <= 0
		|| BUFFER_SIZE >= INT_MAX || read(fd, 0, 0) < 0)
		return (NULL);
	if (buffer[fd] == NULL)
	{
		buffer[fd] = ft_calloc(1, sizeof(char));
		if (buffer[fd] == NULL)
			return (NULL);
	}
	buffer[fd] = read_file(fd, buffer[fd]);
	if (buffer[fd] == NULL)
		return (NULL);
	res = get_line(buffer[fd]);
	buffer[fd] = slide_str(buffer[fd]);
	return (res);
}
