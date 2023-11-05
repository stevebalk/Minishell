/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:54:48 by sbalk             #+#    #+#             */
/*   Updated: 2023/09/14 16:12:52 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(size_t arg_count, ...)
{
	va_list		args;
	const char	*temp;
	char		*old_str;
	char		str_len;
	char		*ret;

	ret = NULL;
	va_start(args, arg_count);
	while (arg_count--)
	{
		temp = (const char *) va_arg(args, char *);
		if (temp == NULL)
			continue ;
		old_str = ret;
		str_len = ft_strlen(ret) + ft_strlen(temp);
		ret = malloc((str_len + 1) * sizeof(char));
		if (ret == NULL)
			return (NULL);
		if (str_len > 1)
			ft_strlcpy(ret, old_str, ft_strlen(old_str) + 1);
		ft_strlcat(ret, temp, str_len + 1);
		if (old_str != NULL)
			free(old_str);
	}
	return (ret);
}
