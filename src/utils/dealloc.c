/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:56:55 by jonas             #+#    #+#             */
/*   Updated: 2024/01/04 16:47:39 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

void	ini_var_names_to_null(t_var_names *var)
{
	var->raw_copy = NULL;
	var->raw_value = NULL;
	var->value_added_quotes = NULL;
	var->value_without_quotes = NULL;
	var->var_name = NULL;
	var->has_equal = 0;
}

void	dealloc_var_names(t_var_names *var)
{
	if (var->raw_copy)
		free(var->raw_copy);
	if (var->raw_value)
		free(var->raw_value);
	if (var->value_added_quotes)
		free(var->value_added_quotes);
	if (var->value_without_quotes)
		free(var->value_without_quotes);
	if (var->var_name)
		free(var->var_name);
}

// emptys the pointer and set it to NULL
void	free_n_null(void **ptr)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
}
