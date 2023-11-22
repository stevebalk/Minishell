/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:56:55 by jonas             #+#    #+#             */
/*   Updated: 2023/11/22 16:47:06 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	ini_var_names_to_null(t_var_names *var)
{
	var->raw_copy = NULL;
	var->raw_value = NULL;
	var->value_added_quotes = NULL;
	var->value_without_quotes = NULL;
	var->var_name = NULL;
}
void	dealloc_var_names(t_var_names *var)
{
	c_yellow(); printf("dealloc_var_names()\n");c_red();
	if (var->raw_copy)
	{
		printf("free raw copy\n");
		free(var->raw_copy);
	}
	if (var->raw_value)
	{
		printf("free value\n");
		free(var->raw_value);
	}
	if (var->value_added_quotes)
	{
		printf("free value_added_quotes\n");
		free(var->value_added_quotes);
	}
	if (var->value_without_quotes)
	{
		printf("free value_without_quotes\n");
		free(var->value_without_quotes);
	}
	if (var->var_name)
	{
		printf("free var_name\n");
		free(var->var_name);
	}
}