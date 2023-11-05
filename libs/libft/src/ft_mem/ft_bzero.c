/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:59:17 by sbalk             #+#    #+#             */
/*   Updated: 2022/12/25 15:12:07 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t size)
{
	unsigned char	*temp;

	temp = (unsigned char *)s;
	while (size-- > 0)
	{
		*temp = 0;
		temp++;
	}
	s = temp;
}
