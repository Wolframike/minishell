/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 15:42:16 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/25 18:44:27 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include <stdio.h>

int main(void)
{
	char	*input = "echo aaa > outfile | ls | pwd";
	t_state data;

	printf("String to parse: '%s'\n", input);
	puts("=========================");
	puts("AST TYPE LIST");
	puts("0->AST_CMD");
	puts("1->AST_AND");
	puts("2->AST_OR");
	puts("3->AST_PIPE");
	puts("===========================");
	puts("REDIR TYPE LIST");
	puts("0->REDIR_IN");
	puts("1->REDIR_OUT");
	puts("2->REDIR_APPEND");
	puts("3->REDIR_HEREDOC");
	puts("===========================");
	t_ast_node *node = parse(&data, input);
	// print_tokens(data.token);
	puts("In main funtion");
	print_node(node);
	// destroy_token(&data.token);
	destroy_ast_node(node);
}
