/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_strings_a.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:00:37 by jopeters          #+#    #+#             */
/*   Updated: 2024/01/04 16:53:16 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

// returns a string till the first occurence of the given symbol
char	*get_string_till_first_symbol(char *str_in, char symbol)
{
	char	*new_str;
	int		pos_symbol;
	int		i;

	pos_symbol = get_first_symbol_pos(str_in, symbol);
	if (pos_symbol == -1 && !str_in)
		return (NULL);
	if (pos_symbol == -1)
	{
		new_str = get_string_from_string(str_in);
		return (new_str);
	}
	i = 0;
	new_str = str_in;
	while (str_in[i] != symbol)
		i++;
	new_str = (char *)malloc(sizeof(char) * (i + 1));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, str_in, i + 1);
	return (new_str);
}

/* returns a str from the first occurence of the 
given symbol (without the symbol) */
char	*get_string_from_first_symbol(char *str_in, char symbol)
{
	char	*new_str;
	int		pos_symbol;
	int		len;

	pos_symbol = get_first_symbol_pos(str_in, symbol);
	if (pos_symbol == -1 || !str_in)
		return (NULL);
	len = ft_strlen(str_in);
	new_str = (char *)malloc(sizeof(char) * (len - pos_symbol + 1));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, str_in + (pos_symbol + 1), (len - pos_symbol + 1));
	return (new_str);
}

// returns a new string with symbols added in front and at the end
char	*get_string_with_symbols_at_end_and_front(char *str_in, char symbol)
{
	int		i;
	int		i2;
	char	*new_str;

	if (!str_in)
		return (NULL);
	i = 0;
	i2 = 0;
	new_str = (char *)malloc(sizeof(char) *(ft_strlen(str_in) + 3));
	if (!new_str)
		return (NULL);
	new_str[i2++] = symbol;
	while (str_in[i])
		new_str[i2++] = str_in[i++];
	new_str[i2] = symbol;
	new_str[++i2] = '\0';
	return (new_str);
}

// copy the string and allocate a new string
char	*get_string_from_string(char *str_in)
{
	int		len;
	int		i;
	char	*new_str;

	len = ft_strlen(str_in);
	i = -1;
	new_str = (char *)malloc(sizeof(char) *(len + 1));
	if (!new_str)
		return (NULL);
	while (str_in[++i])
		new_str[i] = str_in[i];
	new_str[i] = '\0';
	return (new_str);
}
