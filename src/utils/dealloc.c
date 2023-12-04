/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:56:55 by jonas             #+#    #+#             */
/*   Updated: 2023/12/04 15:09:04 by jopeters         ###   ########.fr       */
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
	#ifdef PRINT_DEALLOC
		c_yellow(); printf("dealloc_var_names()\n");c_red();
	#endif
	if (var->raw_copy)
	{
		#ifdef PRINT_DEALLOC
		printf("   free raw copy\n");
		#endif
		free(var->raw_copy);
	}
	if (var->raw_value)
	{
		#ifdef PRINT_DEALLOC
		printf("   free value\n");
		#endif
		free(var->raw_value);
	}
	if (var->value_added_quotes)
	{
		#ifdef PRINT_DEALLOC
		printf("   free value_added_quotes\n");
		#endif
		free(var->value_added_quotes);
	}
	if (var->value_without_quotes)
	{
		#ifdef PRINT_DEALLOC
		printf("   free value_without_quotes\n");
		#endif
		free(var->value_without_quotes);
	}
	if (var->var_name)
	{
		#ifdef PRINT_DEALLOC
		printf("   free var_name\n");
		#endif
		free(var->var_name);
	}
}

// emptys the pointer and set it to NULL
void	free_n_null(void **ptr)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
}