/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:30:33 by misargsy          #+#    #+#             */
/*   Updated: 2023/12/01 14:07:00 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <stdbool.h>
# include <dirent.h>
# include <sys/stat.h>
# include "error.h"

void	free2darr(char **arr);
bool	is_dir(const char *path);

#endif
