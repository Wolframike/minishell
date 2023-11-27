# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 17:34:48 by misargsy          #+#    #+#              #
#    Updated: 2023/11/27 19:19:31 by misargsy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror -I includes -I libft -I$(shell brew --prefix readline)/include
RLFLAGS = -lreadline -L $(shell brew --prefix readline)/lib
LEXER =		srcs/lexer/lexer_utils.c \
			srcs/lexer/lexer.c \

AST = 		srcs/ast/create_node.c \
			srcs/ast/destroy_node.c \

PARSER = 	srcs/parser/parser.c \
			srcs/parser/parse_and_or.c \
			srcs/parser/parse_simple_command.c \
			srcs/parser/parse_io_file.c \
			srcs/parser/parse_heredoc.c \
			srcs/parser/parse_pipeline.c \
			srcs/parser/parse_cmd_suffix.c \
			srcs/parser/parse_word.c \
			srcs/parser/consume.c \

EXPAND =	srcs/expand/expand.c \
			srcs/expand/split_into_list.c \

SIGNAL =	srcs/signal/signal.c \
			srcs/signal/signal_handler.c \

BUILTIN =	srcs/builtin/bi_echo.c \
			srcs/builtin/bi_cd.c \
			srcs/builtin/bi_cd_util.c \
			srcs/builtin/bi_pwd.c \
			srcs/builtin/bi_export.c \
			srcs/builtin/bi_unset.c \
			srcs/builtin/bi_env.c \
			srcs/builtin/bi_exit.c \
			srcs/builtin/bi_util.c \

EXECUTE =	srcs/exec/execute.c \
			srcs/exec/exec_util.c \
			srcs/exec/exec_pipeline.c \
			srcs/exec/ft_execvp.c \
			srcs/exec/set_redir.c \

ERRORS =	srcs/error/general_errors.c \
			srcs/error/lexer_errors.c \
			srcs/error/bi_errors.c \
			srcs/error/exec_errors.c \

ENV =		srcs/env/init_destroy.c \
			srcs/env/manipulation.c \
			srcs/env/set_env.c \

UTILS =		srcs/utils/free.c \

TESTS = 	tests/parser/print_utils_parser.c \
			tests/lexer/print_utils_lexer.c \

SRCS = srcs/main.c $(LEXER) $(AST) $(PARSER) $(EXPAND) $(SIGNAL) $(BUILTIN) $(EXECUTE) $(ERRORS) $(ENV) $(UTILS) $(TESTS)

NAME = minishell
LIBFT = libft.a

OBJS = $(SRCS:.c=.o)

CHECK		= \033[32m[✔]\033[0m
BLUE		= \033[1;34m
RESET		= \033[0m

SANITIZE = -fsanitize=address

all: $(NAME)

sanitize: clean
sanitize: FLAGS += -fsanitize=address
sanitize: $(NAME)

x: $(NAME)
	@./$(NAME)

valgrind: $(NAME)
	@valgrind --leak-check=full --log-file=valgrind.logs ./$(NAME)
	@printf "\n========================================valgrind leaks========================================\n"
	@grep "definitely lost" valgrind.logs

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(BLUE)Compiling minishell... $(RESET)"
	cc $(FLAGS) $(RLFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(CHECK) $(RESET)"
	@clear

$(LIBFT):
	@echo "$(BLUE)Compiling libft... $(RESET)"
	@make -C libft
	@mv libft/libft.a .
	@echo "$(CHECK) $(RESET)"

%.o: %.c
	@cc $(FLAGS) $(INC) -c $< -o $@

clean:
	@echo "$(BLUE)Removing objects and libraries... $(RESET)"
	@rm -f $(OBJS) $(LIBFT)
	@make clean -C libft
	@echo "$(CHECK) $(RESET)"

fclean: clean
	@echo "$(BLUE)Removing executables... $(RESET)"
	@rm -f $(NAME) $(LIBFT)
	@echo "$(CHECK) $(RESET)"

re:	fclean	all

.PHONY: all bonus clean fclean re
