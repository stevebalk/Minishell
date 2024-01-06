/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:52:28 by sbalk             #+#    #+#             */
/*   Updated: 2024/01/06 12:02:37 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t get_env_var_name_len(char *str)
{
	char *cur;

	cur = str;
	cur++;
	while (*cur && (ft_isalnum(*cur) || *cur == '_'))
		cur++;
	return (cur - str);
}

void concatinate_line_input_to_str(char **dst, char *src)
{
	char *temp;

	temp = *dst;
	*dst = malloc(ft_strlen(temp) + ft_strlen(src) + 2);
	if (temp != NULL)
	{
		ft_strlcpy(*dst, temp, ft_strlen(temp) + 1);
		ft_strlcat(*dst, src,
				   ft_strlen(*dst) + ft_strlen(src) + 1);
		ft_strlcat(*dst, "\n", ft_strlen(*dst) + 2);
		free(temp);
	}
	else
	{
		ft_strlcpy(*dst, src, ft_strlen(src) + 1);
		ft_strlcat(*dst, "\n", ft_strlen(*dst) + 2);
	}
}
