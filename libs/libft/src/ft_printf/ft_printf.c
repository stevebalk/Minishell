/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:48:12 by sbalk             #+#    #+#             */
/*   Updated: 2023/06/01 16:23:14 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static void	ft_choose_print_func(const char *str, t_print *f)
{
	f->speci = *str;
	if (*str == 'c' || *str == '%')
		ft_print_char(f);
	else if (*str == 'd' || *str == 'i' || *str == 'u')
		ft_print_d_i_u(f);
	else if (*str == 's')
		ft_print_string(f);
	else if (*str == 'x' || *str == 'X')
		ft_print_hex(f);
	else if (*str == 'p')
		ft_print_p(f);
}

int	ft_printf(const char *str, ...)
{
	t_print	a;
	t_print	*f;
	int		ret;

	f = &a;
	ft_reset_t_print(f);
	f->tl = 0;
	va_start(f->args, str);
	ret = 0;
	while (*str)
	{
		if (*str != '%')
			ret += write(1, str++, 1);
		else
		{
			str = ft_eval_format(f, str + 1);
			ft_choose_print_func(str++, f);
			ft_reset_t_print(f);
		}
	}
	va_end(f->args);
	ret += f->tl;
	return (ret);
}
