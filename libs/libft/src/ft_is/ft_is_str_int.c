/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_str_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:31:08 by sbalk             #+#    #+#             */
/*   Updated: 2023/08/02 17:07:45 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_str_int(char *str)
{
	ssize_t	nbr;

	if (!ft_is_str_num(str))
		return (0);
	nbr = ft_atolli(str);
	if (nbr < INT_MIN || nbr > INT_MAX)
		return (0);
	return (1);
}
