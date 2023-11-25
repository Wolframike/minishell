/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils_lexer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:28:29 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/25 16:36:52 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>

void	print_tokens(t_token *token)
{
	if (token == NULL)
	{
		puts("(null)");
		puts("===========================");
	}
	else
	{
		printf("Token word: %s\n", token->word);
		printf("Token type: %d\n", token->type);
		print_tokens(token->next);
	}
}
