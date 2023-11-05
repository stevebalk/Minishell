/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:18:33 by sbalk             #+#    #+#             */
/*   Updated: 2023/05/15 17:54:05 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Search and return a pointer to the LAST occourrence of character c
char	*ft_strrchr(const char *s, int c)
{
	const char	*latest;

	latest = NULL;
	while (*s)
	{
		if (*s == (char) c)
			latest = s;
		s++;
	}
	if ((char) c == '\0')
		return ((char *) s);
	return ((char *) latest);
}
