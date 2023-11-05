/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:20:01 by sbalk             #+#    #+#             */
/*   Updated: 2023/07/31 12:07:04 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static	size_t	parse_precision(t_print *f, const char *str)
{
	size_t	i;

	i = 1;
	f->point = 1;
	str++;
	f->set = 0;
	f->zero = 0;
	while (!ft_strchr(SPECIFIERS, *str))
	{
		if (!f->set && ft_isdigit(*str))
		{
			f->prec = ft_atoi(str);
			f->set = 1;
		}
		str++;
		i++;
	}
	return (i);
}

static	size_t	parse_width(t_print *f, const char *str)
{
	size_t	i;

	i = 0;
	f->set = 1;
	f->width = ft_atoi(str);
	str++;
	while (ft_isdigit(*str))
	{
		str++;
		i++;
	}
	return (i);
}

const char	*ft_eval_format(t_print *f, const char *str)
{
	while (!ft_strchr(SPECIFIERS, *str) && *str != '.')
	{
		if (*str == '-')
			f->left_allign = 1;
		else if (*str == '+')
			f->sign = 1;
		else if (*str == ' ')
			f->space = 1;
		else if (*str == '#')
			f->hashtag = 1;
		else if (*str == '0' && !ft_isdigit(*(str - 1)))
			f->zero = 1;
		else if (*str > '0' && *str <= '9' && !f->set)
			str += parse_width(f, str);
		str++;
	}
	if (*str == '.')
		str += parse_precision(f, str);
	return (str);
}
