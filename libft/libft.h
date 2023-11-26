/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:02:40 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/26 12:56:17 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdarg.h>
# include <stdbool.h>

# define LOWER_HEX "0123456789abcdef"
# define UPPER_HEX "0123456789ABCDEF"
# define SPECIFIER "cspdiuxX%"
# define BUFFER_SIZE 42
# define FD_MAX 25476

typedef struct s_list
{
	struct s_list	*prev;
	struct s_list	*next;
	void			*content;
}	t_list;

typedef struct s_flags
{
	bool	left_align;
	bool	zero_padding;
	bool	sign;
	bool	sharp;
	bool	period;
	bool	space;
	bool	set_width;
	bool	precision;
}	t_flags;

typedef struct s_format
{
	t_flags	flags;
	int		width;
	int		precision;
	char	specifier;
}	t_format;

int			ft_atoi(const char *str);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
char		*ft_itoa(int n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memset(void *b, int c, size_t len);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);
char		**ft_split(char const *s, char c);
char		*ft_strchr(const char *s, int c);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *src);
char		*ft_strndup(char *src, size_t len);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcat(char *dest, const char *src, size_t size);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
size_t		ft_strlen(const char *s);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strrchr(const char *s, int c);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_toupper(int c);
int			ft_tolower(int c);

t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

void		printf_c(t_format info, int c, int *len);
void		printf_s(t_format info, char *s, int *len);
void		printf_d_i(t_format info, int n, int *len);
void		printf_u(t_format info, unsigned int n, int *len);
void		printf_x(t_format info, unsigned int n, int *len);
void		printf_x_upper(t_format info, unsigned int n, int *len);
void		printf_p(t_format info, void *ptr, int *len);
void		printf_percent(t_format info, int *len);
int			ft_putchar(char c);
int			ft_putstr(char *s);
int			ft_printf(const char *s, ...);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *src);
int			ft_max(int a, int b);
int			digit_count(long value, int base_size);
char		*ft_itoa_decimal(int value);
char		*ft_itoa_positive_hex(unsigned long value);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
void		ft_putnbr_sub(int n, long long *weight, long long *lnb);
void		ft_putxnbr_sub(unsigned int n, long long *weight, long long *lnb);
void		ft_putunbr_sub(unsigned int n, long long *weight, long long *lnb);
void		print_hex(long long weight, long long lnb, bool is_large, int *len);
int			get_printhlen(t_format info, unsigned int n);
void		get_puthchrs(t_format info, unsigned int n,
				char *fill, char *putsign);
int			process_hgap(t_format *info, char putsign,
				unsigned int n, char fill);
t_format	parse_flags(const char **s);

char		*get_next_line(int fd);

int			ft_min(int a, int b);
int			ft_max(int a, int b);
int			ft_abs(int a);
int			ft_strcmp(char *s1, char *s2);

#endif
