/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:58:32 by sbalk             #+#    #+#             */
/*   Updated: 2023/09/18 17:56:57 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	free_list(char **list, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(list[i]);
		i++;
	}
	free(list);
}

static char	**fill_list(const char *s, char **list, size_t string_count, char c)
{
	size_t	i;
	char	*p;
	size_t	str_len;

	i = 0;
	while (i < string_count)
	{
		str_len = 0;
		while (*s == c)
			s++;
		while (*s != c && *s != '\0')
		{
			str_len++;
			s++;
		}
		p = (char *) malloc((str_len + 1) * sizeof(char));
		if (p == NULL)
		{
			free_list(list, i + 1);
			return (NULL);
		}
		ft_strlcpy(p, s - str_len, str_len + 1);
		list[i++] = p;
	}
	return (list);
}

char	**ft_split(char const *s, char c)
{
	char	**list;
	size_t	string_count;
	size_t	i;

	i = 0;
	string_count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
			string_count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	list = (char **)ft_calloc((string_count + 1), sizeof(char *));
	if (list == NULL)
		return (NULL);
	list = fill_list(s, list, string_count, c);
	return (list);
}
