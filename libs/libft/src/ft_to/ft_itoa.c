/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:59:03 by sbalk             #+#    #+#             */
/*   Updated: 2023/08/02 16:30:02 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_int_length(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		length;
	char	*str;

	length = get_int_length(n);
	str = malloc((length + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	if (n < 0)
		str[0] = '-';
	str[length] = '\0';
	if (n == 0)
		str[0] = '0';
	while (n != 0)
	{
		str[length - 1] = ft_abs(n % 10) + '0';
		n /= 10;
		length--;
	}
	return (str);
}
