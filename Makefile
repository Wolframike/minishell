# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 17:34:48 by misargsy          #+#    #+#              #
#    Updated: 2023/11/18 20:01:46 by knishiok         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror  -I includes -I libft/includes
RLFLAGS = -lreadline

LEXER = srcs/lexer/lexer_utils.c \
	srcs/lexer/lexer.c \
	srcs/main.c \
	srcs/utils/errors.c

SRCS = srcs/main.c $(LEXER)

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
	@cc $(FLAGS) $(INC) $(RLFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
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
