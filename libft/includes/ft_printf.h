/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 23:01:23 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/13 18:27:31 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <limits.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdint.h>

# define HEX_NUM_LC "0123456789abcdef"
# define HEX_NUM_UC "0123456789ABCDEF"
# define DEC_NUM "0123456789"
# define FLAGS "-0.# +"
# define CONVS "cspdiuxX%"

typedef struct s_format
{
	bool	f_plus;
	bool	f_minus;
	bool	f_zero;
	bool	f_space;
	bool	f_dot;
	bool	f_hash;
	size_t	prec;
	size_t	width;
}	t_format;

int				ft_dprintf(const int fd, const char *format, ...);

ssize_t			ftpf_main(char *format, va_list args);
ssize_t			ftpf_printer(char **format, va_list args);
ssize_t			ftpf_phelper(char c, t_format *fstruct, va_list args);

t_format		*ftpf_fparse(char *format);

t_format		*fstruct_init(void);
size_t			get_width(char *format);
size_t			get_prec(char *format, t_format *fstruct);
bool			get_zero(char *format);

bool			is_flag(const char c);
bool			is_conv(const char c);

bool			ftpf_sign_first(int n, t_format *fstruct);
bool			ftpf_hash_first(unsigned long n, t_format *fstruct);
size_t			ftpf_fillerlen(long long n, int base, t_format *fstruct);

int				ftpf_print_char(t_format *fstruct, char c);
int				ftpf_print_str(t_format *fstruct, char *str);
void			ft_putnbr_phex(uintptr_t n, char *base,
					bool prefix, t_format *fstruct);
int				ftpf_print_ptr(t_format *fstruct, void *ptr);
int				ftpf_print_percent(t_format *fstruct);

int				ftpf_print_int(t_format *fstruct, int n);
int				ftpf_print_uint(t_format *fstruct, unsigned int n);
size_t			ftpf_numlen(long long n, int base, t_format *fstruct);
int				ftpf_print_sign(int n, t_format *fstruct);
size_t			ftpf_align(size_t total, size_t width);

int				ftpf_print_hex(t_format *fstruct,
					unsigned int n, const char *base);
int				ftpf_print_hash(unsigned long n, bool upper, t_format *fstruct);

unsigned int	ft_atoui(const char *str);
void			ftpf_ps_cap(char *str, int fd, t_format *fstruct);
void			ft_putunbr_fd(uintmax_t n, const char *base, int fd);
size_t			ftpf_putsign_fd(int n, int fd);
size_t			ft_numlen(intmax_t n, int base);
size_t			ft_ulnumlen(uintmax_t n, int base);
void			ft_putabsnbr_fd(intmax_t n, int fd);
size_t			ft_max(size_t a, size_t b);

#endif