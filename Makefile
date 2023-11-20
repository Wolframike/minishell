# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 17:34:48 by misargsy          #+#    #+#              #
#    Updated: 2023/11/21 02:06:41 by misargsy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror -I includes -I libft
RLFLAGS = -lreadline

LEXER =		srcs/lexer/lexer_utils.c \
			srcs/lexer/lexer.c \
			srcs/utils/errors.c \

BUILTIN =	srcs/builtin/bi_util.c \
			srcs/builtin/bi_echo.c \
			srcs/builtin/bi_exit.c \
			srcs/builtin/bi_pwd.c \

EXEC =		srcs/exec/execute.c \
			srcs/exec/exec_pipeline.c \
			srcs/exec/set_redir.c \
			srcs/exec/ft_execvp.c \
			srcs/exec/exec_error.c \

SRCS = srcs/main.c $(LEXER) $(BUILTIN) $(EXEC)

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
