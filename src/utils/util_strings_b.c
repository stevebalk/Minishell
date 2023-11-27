/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_strings_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:09:30 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/27 14:17:33 by jopeters         ###   ########.fr       */
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
		str[nl_pos] = '\0';
}

// returns the pos of the first occurence of a given symbol;
// if there is no symbol return val is -1
int	get_first_symbol_pos(char *str, char symbol)
{
	int	i;

	i = -1;
	while (i++, str[i])
	{
		if (str[i] == symbol)
			return (i);
	}
	return (-1);
}

// return 1 if symbol is in str otherwise 0
int	has_str_symbol(char *str, char symbol)
{
	if (get_first_symbol_pos(str, symbol) > -1)
		return (1);
	else
		return (0);
}

// return 1 if a specific symbol is on a specific position in a string
int	is_s_in_pos_of_str(char *str, int pos, char symbol)
{
	int	i;

	i = -1;
	while (i++, str[i])
	{
		if (i == pos && str[i] == symbol)
			return (1);
	}
	return (0);
}
