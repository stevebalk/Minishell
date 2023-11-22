/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_temp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:50:37 by jonas             #+#    #+#             */
/*   Updated: 2023/11/22 16:49:46 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

/*
Temporäre Funktionen von Jonas ... sollte in vor dem Release gelöscht, oder wenn benötigt verschoben werden

*/

void show_var_names(t_var_names *var)
{
	c_purple(); printf("show_var_names() \n"); 
	c_blue(); fflush(stdout);
	
	printf("   raw_copy >%s<\n", var->raw_copy);
	printf("   var_name >%s<\n", var->var_name);
	printf("   raw_value >%s<\n", var->raw_value);
	printf("   value_without_quotes >%s<\n", var->value_without_quotes);
	printf("   value_added_quotes >%s<\n", var->value_added_quotes);

	c_reset();
}