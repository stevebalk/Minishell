/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:21:55 by sbalk             #+#    #+#             */
/*   Updated: 2023/07/31 12:07:11 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static size_t	ft_puthex(size_t nbr, t_print *f)
{
	size_t	rtn;

	rtn = 0;
	if (nbr >= 16)
		rtn += ft_puthex(nbr / 16, f);
	if (f->speci == 'X')
		ft_putchar_fd(HEXAUP[nbr % 16], 1);
	else
		ft_putchar_fd(HEXALOW[nbr % 16], 1);
	return (rtn + 1);
}

static char	*hashtag(t_print *f)
{
	if (f->speci == 'X')
		return ("0X");
	return ("0x");
}

void	ft_print_hex(t_print *f)
{
	unsigned int	nbr;
	int				len;

	nbr = va_arg(f->args, unsigned int);
	len = ft_nbrlen(nbr, 16);
	if (!nbr && f->point && !f->prec)
		len = 0;
	if (f->prec < len || !f->point)
		f->prec = len;
	if (f->hashtag && nbr)
		f->width -= 2;
	f->tl += ft_putnstr_fd(hashtag(f), 1, 2 * (f->hashtag && nbr && f->zero));
	if (!f->left_allign && !f->point && f->prec && f->zero)
		f->tl += ft_putnchar_fd('0', 1, f->width - len);
	else if (!f->left_allign && f->width > f->prec)
		f->tl += ft_putnchar_fd(' ', 1, f->width - f->prec);
	f->tl += ft_putnstr_fd(hashtag(f), 1, 2 * (f->hashtag && nbr && !f->zero));
	f->tl += ft_putnchar_fd('0', 1, (f->prec - len));
	if (len)
		f->tl += ft_puthex(nbr, f);
	if (f->left_allign && f->width > f->prec)
		f->tl += ft_putnchar_fd(' ', 1, f->width - f->prec);
}

void	ft_print_p(t_print *f)
{
	size_t	nbr;
	int		len;

	nbr = va_arg(f->args, size_t);
	len = ft_nbrlen(nbr, 16);
	if (nbr == ULONG_MAX)
		len = 16;
	if (f->prec < len || !f->point)
		f->prec = len;
	f->width -= 2;
	f->tl += ft_putnstr_fd("0x", 1, 2 * f->zero);
	if (!f->left_allign && !f->point && f->prec && f->zero)
		f->tl += ft_putnchar_fd('0', 1, f->prec - len);
	else if (!f->left_allign && f->width > f->prec)
		f->tl += ft_putnchar_fd(' ', 1, f->width - f->prec);
	f->tl += ft_putnstr_fd("0x", 1, 2 * !f->zero);
	f->tl += ft_putnchar_fd('0', 1, f->prec - len);
	if (len)
		f->tl += ft_puthex(nbr, f);
	if (f->left_allign && f->width > f->prec)
		f->tl += ft_putnchar_fd(' ', 1, f->width - f->prec);
}
