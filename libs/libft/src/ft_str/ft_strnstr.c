/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:47:35 by sbalk             #+#    #+#             */
/*   Updated: 2023/05/17 16:48:06 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*haystack_tmp;
	char	*needle_tmp;

	if (!ft_strlen(needle))
		return ((char *) haystack);
	if (!ft_strlen(haystack) || ft_strlen(needle) > len)
		return (NULL);
	len = len - ft_strlen(needle) + 1;
	while (len-- && *haystack)
	{
		haystack_tmp = (char *) haystack;
		needle_tmp = (char *) needle;
		while (*needle_tmp && *haystack_tmp == *needle_tmp)
		{
			haystack_tmp++;
			needle_tmp++;
		}
		if (!*needle_tmp)
			return ((char *) haystack);
		haystack++;
	}
	return (NULL);
}
