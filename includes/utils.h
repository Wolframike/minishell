/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:30:33 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/11 11:05:24 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "type.h"
# include "error.h"
# include <stdlib.h>
# include <stdbool.h>
# include <dirent.h>
# include <sys/stat.h>

bool	strdup_case_null(char **res, const char *src);
void	free2darr(char **arr);
bool	is_dir(const char *path);
bool	judge_executable(const char *line);

#endif
