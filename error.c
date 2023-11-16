/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:22:44 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/15 15:59:36 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	spit_error(bool is_perror, char *msg)
{
	if (is_perror)
		perror(msg);
	else
		fprintf(stderr, "%s: %s\n", SHELL_NAME, msg);
}
