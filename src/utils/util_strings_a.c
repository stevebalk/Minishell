/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_strings_a.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:00:37 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/23 13:16:35 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

// returns a string till the first occurence of the given symbol
char	*get_string_till_first_symbol(char *str_in, char symbol)
{
	char	*new_str;
	int		pos_symbol;
	int		i;

	pos_symbol = get_first_symbol_pos(str_in, symbol);
	c_yellow(); printf("get_string_til_first_symbol()  str_in >%s<   symbol >%c<  pos symbol: %i\n", str_in, symbol, pos_symbol);
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
	printf("i: %i \n", i);
	new_str = (char *)malloc(sizeof(char) * (i + 1));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, str_in, i + 1);
	c_red();printf("~get_string_til_first_symbol() >%s<\n", new_str);
	return (new_str);
}

// returns a string from the first occurence of the given symbol (witout the symbol)
char	*get_string_from_first_symbol(char *str_in, char symbol)
{
	char	*new_str;
	int		pos_symbol;
	int		len;
	
	pos_symbol = get_first_symbol_pos(str_in, symbol);
	c_yellow(); printf("get_string_from_first_symbol()  str_in >%s<   symbol >%c<  pos_symbol: %i\n", str_in, symbol, pos_symbol);
	if (pos_symbol == -1 || !str_in)
		return (NULL);
	len = ft_strlen(str_in);
	
	//printf("len %i \n", len);
	new_str = (char *)malloc(sizeof(char) * (len-pos_symbol + 1));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, str_in + (pos_symbol + 1), (len-pos_symbol + 1));
	c_red();printf("~sget_string_from_first_symbol>%s<\n", new_str);
	return (new_str);
}

// returns a string witout given symbols
char	*get_string_without_symbols(char *str_in, char symbol)
{
    c_yellow(); printf("get_string_without_symbols()  str_in >%s<   symbol >%c< \n", str_in, symbol);

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
	c_green(); printf("count: %i   str_len: %i\n", count, (int)ft_strlen(str_in) );
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
    c_red(); printf(" --->string without %c  >%s< \n", symbol, new_str);
	return (new_str);
}

// returns a new string with symbols added in front and at the end
char *get_string_with_symbols_at_end_and_front(char *str_in, char symbol)
{
	int		i;
	int		i2;
	char	*new_str;
    c_yellow(); printf("get_string_with_symbols_at_end_and_front()  str_in >%s<   symbol >%c< \n", str_in, symbol);
	fflush(stdout);
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
	//printf("i2: %i\n", i2);
	c_red(); printf(" --->string with front end %c  >%s< \n", symbol, new_str);

	return (new_str);
}

// copy the string and allocate a new string
char *get_string_from_string(char *str_in)
{
	int		len;
	int		i;
	char	*new_str;

	len = ft_strlen(str_in);
	c_yellow(); printf("get_string_from_string  str_in >%s<   len: %i \n", str_in, len);

	i = -1;
	new_str = (char *)malloc(sizeof(char) *(len + 1));
	if (!new_str)
		return (NULL);

	while(str_in[++i])
		new_str[i] = str_in[i];

	new_str[i] = '\0';
	c_red(); printf("~get_string_from_string  str_in >%s<   len: %i \n", new_str, (int)ft_strlen(new_str));

	return (new_str);
}


char *join_three_string(char *str1, char *str2, char *str3)
{
	c_yellow(); printf("join_three_string() s1 >%s<   s2 >%s<   s3 >%s<\n", str1, str2, str3); 

	char *new_str;
	//printf("len 1: %i     2: %i   3: %i\n", (int)ft_strlen(str1), (int)ft_strlen(str2), (int)ft_strlen(str3));
	new_str = (char *)ft_calloc((ft_strlen(str1)+ft_strlen(str2)+ft_strlen(str3) + 1), sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strlcat(new_str, str1, ft_strlen(str1) + 1);
	ft_strlcat(new_str, str2, ft_strlen(new_str) + ft_strlen(str2) + 1);
	ft_strlcat(new_str, str3, ft_strlen(new_str) + ft_strlen(str3) + 1);

	c_red(); printf("~join_three_string() s >%s<  \n", new_str); 
	return new_str;
}
