/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:39:12 by sbalk             #+#    #+#             */
/*   Updated: 2024/01/05 12:14:48 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Checks if variable is "$?" alias last exit code */
size_t	is_exit_code_variable(const char *str)
{
	if (ft_strncmp(str, "$?", 2) == 0)
		return (1);
	return (0);
}

/* Checks if a env varible has a numerical value behind
the $, like $2 */
int	is_numerical_variable(char *str)
{
	if (str[0] == '$' && ft_isdigit(str[1]))
		return (1);
	return (0);
}

/* Checks if a env variable has something behind it that isn't 
alphabetical or an underscore, for example $// or $.. or $2 */
int	is_metachar_variable(char *str)
{
	if (str[0] == '$' && !ft_isalpha(str[1]) && str[1] != '_')
		return (1);
	return (0);
}
