/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 23:53:14 by sbalk             #+#    #+#             */
/*   Updated: 2023/06/01 16:09:45 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

// 	args		= va_arg
//	speci		= Specifiers cspdiuxX%
//	width		= 1... minimum characters to print (padding)
//	prec		= specifies the precision (depends of the parameter)
//	zero		= 0 print leading zeroes (zero padding)
//	point		= . track if precision is set
//	left_allign	= left allign
//	tl			= counts the total length
//	sign		= Show + sign in front of positive number
//	space		= should a space be printed / used with + for proper allignment
//	hashtag		= alternativ printing for x and X
//	set;		= needed for tracking in width and precision check

typedef struct s_print
{
	va_list	args;
	char	speci;
	int		width;
	int		prec;
	int		zero;
	int		point;
	int		left_allign;
	size_t	tl;	
	int		sign;
	int		space;
	int		hashtag;
	int		set;
}	t_print;

/* String containing printf's specifiers */
# define SPECIFIERS	"cspdiuxX%"

/* Hexadecimal base */

# define HEXALOW	"0123456789abcdef"
# define HEXAUP		"0123456789ABCDEF"

void		ft_reset_t_print(t_print *f);
const char	*ft_eval_format(t_print *f, const char *str);
int			ft_printf(const char *str, ...);

/* UTILITY */

int			ft_putnchar_fd(const char ch, int fd, int len);
int			ft_putnstr_fd(const char *str, int fd, int n);
char		*ft_uitoa(unsigned int nbr);
int			ft_nbrlen(unsigned long long nbr, int base);

// PRINT FUNCTIONS

void		ft_print_char(t_print *f);
void		ft_print_string(t_print *f);
void		ft_print_d_i_u(t_print *f);
void		ft_print_hex(t_print *f);
void		ft_print_p(t_print *f);

#endif