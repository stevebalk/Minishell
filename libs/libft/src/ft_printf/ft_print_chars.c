/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_chars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:21:17 by sbalk             #+#    #+#             */
/*   Updated: 2023/06/01 16:21:46 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_putnchar_fd(const char ch, int fd, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		write(fd, &ch, 1);
		i++;
	}
	return (i);
}

/* Prints string until n-th size or '/0' to the given
file descriptor and returns number of wrote chars*/
int	ft_putnstr_fd(const char *str, int fd, int n)
{
	int	i;

	i = 0;
	while (i < n && *str != '\0')
	{
		i += ft_putnchar_fd(*str, fd, 1);
		str++;
	}
	return (i);
}

/* Print formatted char */
void	ft_print_char(t_print *f)
{
	int	ch;

	ch = '%';
	if (f->speci != '%')
		ch = va_arg(f->args, int);
	if (f->left_allign)
		f->tl += write(1, &ch, 1);
	while (f->width > 1)
	{
		f->tl += write(1, " ", 1);
		f->width--;
	}
	if (!f->left_allign)
		f->tl += write(1, &ch, 1);
}

/* Print formatted string */
void	ft_print_string(t_print *f)
{
	const char	*str;
	int			len;

	str = (const char *) va_arg(f->args, char *);
	if (str == NULL)
		str = "(null)";
	len = ft_strlen(str);
	if (f->point && len > f->prec)
		len = f->prec;
	if (f->left_allign)
		f->tl += ft_putnstr_fd(str, 1, len);
	while (f->width > len)
	{
		f->tl += write(1, " ", 1);
		f->width--;
	}
	if (!f->left_allign)
		f->tl += ft_putnstr_fd(str, 1, len);
}
