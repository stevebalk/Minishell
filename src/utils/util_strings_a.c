/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_strings_a.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:00:37 by jopeters          #+#    #+#             */
/*   Updated: 2024/01/04 16:44:46 by jonas            ###   ########.fr       */
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

// returns a string witout given symbols
char	*get_string_without_symbols(char *str_in, char symbol)
{
	int		count;
	int		i;
	int		i2;
	char	*new_str;

	if (!str_in)
		return (NULL);
	i = -1;
	count = 0;
	while (i++, str_in[i])
	{
		if (str_in[i] == symbol)
			count++;
	}
	new_str = (char *)malloc(sizeof(char) *((int)ft_strlen(str_in) - count + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	i2 = 0;
	while (str_in[i])
	{
		if (str_in[i] != symbol)
			new_str[i2++] = str_in[i];
		i++;
	}
	new_str[i2] = '\0';
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


char	*join_three_string(char *str1, char *str2, char *str3)
{
	char	*new_str;
	int		len[3];

	len[0] = ft_strlen(str1);
	len[1] = ft_strlen(str2);
	len[2] = ft_strlen(str3);
	new_str = (char *)ft_calloc((len[0] + len[1] + len[2] + 1), sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strlcat(new_str, str1, len[0] + 1);
	ft_strlcat(new_str, str2, ft_strlen(new_str) + len[1] + 1);
	ft_strlcat(new_str, str3, ft_strlen(new_str) + len[2] + 1);
	return (new_str);
}
