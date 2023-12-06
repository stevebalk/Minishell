/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:29:24 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/06 18:22:50 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_quotes(const char *str)
{
	while (!is_quote(str) && *str != '\0')
		str++;
	if (is_quote(str))
		return (1);
	return (0);
}

size_t	get_new_delim_len(char *str)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '$')
			{
				len += 2;
				i++;
			}
			else if (!is_quote(str + i + 1))
				len++;
		}
		else if (!is_quote(str + i))
			len++;
		i++;
	}
	return (len);
}

void	expand_dollar_sign(char *dst, char *src,
							size_t *src_pos, size_t *dst_pos)
{
	if (is_quote(&(src[*src_pos + 1])))
		return ;
	else if (src[*src_pos + 1] == '$')
	{
		dst[*dst_pos] = src[*src_pos];
		dst[*dst_pos + 1] = src[*src_pos + 1];
		(*src_pos)++;
		(*dst_pos) += 2;
	}
	else
	{
		dst[*dst_pos] = src[*src_pos];
		(*dst_pos)++;
	}
}

char	*expand_delimiter(char *str)
{
	char	*new_delimiter;
	size_t	len;
	size_t	src_pos;
	size_t	dst_pos;

	len = get_new_delim_len(str);
	new_delimiter = ft_calloc(len + 1, sizeof(char));
	src_pos = 0;
	dst_pos = 0;
	while (str[src_pos] != '\0')
	{
		if (str[src_pos] == '$')
			expand_dollar_sign(new_delimiter, str, &src_pos, &dst_pos);
		else if (!is_quote(str + src_pos))
			new_delimiter[dst_pos++] = str[src_pos];
		src_pos++;
	}
	return (new_delimiter);
}

void	heredoc(char *delimiter)
{
	int		should_expand_env_var;
	char	*expanded_delim;
	
	expanded_delim = NULL;

	should_expand_env_var = has_quotes(delimiter);
	if (should_expand_env_var)
		expanded_delim = expand_delimiter(delimiter);
		
	printf("Old: %s\n", delimiter);
	printf("New: %s\n", expanded_delim);
}
