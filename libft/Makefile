# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/20 09:55:58 by knishiok          #+#    #+#              #
#    Updated: 2023/11/26 12:23:46 by misargsy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -I .
NAME = libft.a
ARFLAGS = rc

SRCS = ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_itoa.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_strndup.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_lstadd_back.c \
	ft_lstadd_front.c \
	ft_lstclear.c \
	ft_lstdelone.c \
	ft_lstiter.c \
	ft_lstlast.c \
	ft_lstmap.c \
	ft_lstnew.c \
	ft_lstsize.c

SRCS += ft_printf.c \
	printf_parse.c \
	printf_c_s_percent.c \
	printf_d_i.c \
	printf_u.c \
	printf_x.c \
	printf_upper_x.c \
	printf_putnbrs.c \
	printf_int_to_string.c \
	printf_int_to_hex.c \
	printf_put_utils.c \

SRCS += get_next_line.c \

SRCS += ft_strcmp.c \
	ft_min.c \
	ft_max.c \
	ft_abs.c

OBJS_NAME = $(SRCS:.c=.o)
OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_NAME))

CHECK		= \033[35m[✔]\033[0m
REMOVE		= \033[31m[✘]\033[0m
GENERATE	= \033[33m[➤]\033[0m

RED			= \033[1;31m
GREEN		= \033[1;32m
YELLOW		= \033[1;33m
BLUE		= \033[1;34m
PURPULE		= \033[1;35m
CIAN		= \033[1;36m
WHITE		= \033[1;37m
RESET		= \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(ARFLAGS) $@ $^
	@ printf "$(CHECK) $(GREEN)Libft successfuly complied!\n$(RESET)"

objs/%.o: %.c
	@mkdir -p $(OBJS_DIR)
	@ printf "$(GENERATE) $(YELLOW)Generating $@... %-50.50s\r$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -r objs
	@echo "$(CHECK) $(CIAN)Successfuly delted object files!$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(CHECK) $(CIAN)Successfuly delted $(NAME)!$(RESET)"

re: fclean all

.PHONY: all clean fclean re