/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:56:55 by jonas             #+#    #+#             */
/*   Updated: 2023/11/22 10:57:27 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	dealloc_var_names(t_var_names *var)
{
	free(var->raw);
	free(var->value);
	free(var->value_added_quotes);
	free(var->value_without_quotes);
	free(var->var_name);
}