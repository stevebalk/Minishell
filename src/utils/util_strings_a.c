/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_strings_a.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:00:37 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/20 16:45:54 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

// returns the position of \n otherwise -1
int	find_newline(char *str)
{
	int	i;
	int	nl;

    i = 0;
    nl = -1;

	while (str[i])
	{
		if (str[i] == '\n')
			nl = i;
		i++;
	}

	return (nl);
}

// replaced the first \n by \0
void	del_first_nl(char *str)
{
	int	nl_pos;

	nl_pos = find_newline(str);
	if (nl_pos >= 0)
		str[nl_pos]= '\0';
}

char	*get_string_till_first_symbol(char *str_in, char symbol)
{
	char	*new_str;
	int		i;

	i = 0;
	new_str = str_in;

	while (str_in[i] != symbol)
		i++;
	c_yellow(); printf("get_string_til_first_symbol()  str_in >%s<   symbol >%c< \n", str_in, symbol);
	printf("i: %i \n", i);
	new_str = (char *)malloc(sizeof(char) * (i + 1));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, str_in, i + 1);
	printf("string end >%s<\n", new_str);
	return (new_str);
}

char	*get_string_without_symbols(char *str_in, char symbol)
{
    c_yellow(); printf("get_string_without_symbols()  str_in >%s<   symbol >%c< \n", str_in, symbol);

	int		count;
	int		i;
	int		i2;
	char	*new_str;

	i = -1;
	count = 0;
	while (i++, str_in[i])
	{
		if (str_in[i] == symbol)
			count++;
	}
	new_str = (char *)malloc(sizeof(char) *(ft_strlen(str_in) - count + 1));
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

    c_purple(); printf(" --->string without %c  >%s< \n", symbol, new_str);
	return (new_str);
}

char *add_symbols_tp_end_and_front(char *str_in, char symbol)
{
	int		i;
	int		i2;
	char	*new_str;

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