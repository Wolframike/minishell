#include "parser.h"
#include <stdio.h>

int main(void)
{
	t_state data;

	t_ast_node *node = parse(&data, "< ls || cat main.c");
	printf("In main funtion:\n");
	print_node(node);
	destroy_token(&data.token);
	destroy_ast_node(node);
}
