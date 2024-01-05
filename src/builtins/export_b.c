/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:22:34 by jopeters          #+#    #+#             */
/*   Updated: 2024/01/05 15:01:43 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

// returns 1 if c is alpha or _
int	check_first_c(char c)
{
	if (ft_isalpha(c))
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

// returns 1 if c is alpha, _ or digit
int	check_other_c(char c)
{
	if (ft_isalpha(c))
		return (1);
	if (ft_isdigit(c))
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

// return 1 if var name is valid; checks only till =
int	check_var_name(char *str)
{
	int	i;

	i = -1;
	if (ft_strlen(str) == 1 && str[0] == '=')
		return (0);
	while (i++, str[i] && str[i] != '=')
	{
		if (i == 0 && !check_first_c(str[i]))
			return (0);
		if (i > 0 && !check_other_c(str[i]))
			return (0);
	}
	return (1);
}

// updated var with all var names and values
void	get_var_names(t_var_names *var, char *str)
{
	var->has_equal = has_str_symbol(str, '=');
	var->raw_copy = get_string_from_string(str);
	var->var_name = get_string_till_first_symbol(str, '=');
	var->raw_value = get_string_from_first_symbol(str, '=');
	var->value_without_quotes = get_string_without_symbols(var->raw_value, '"');
	var->value_added_quotes = get_string_with_symbols_at_end_and_front
		(var->value_without_quotes, '"');
}
