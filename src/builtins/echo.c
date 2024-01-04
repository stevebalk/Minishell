/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:43:21 by jonas             #+#    #+#             */
/*   Updated: 2024/01/04 15:29:42 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	builtin_echo(char **str_arr)
{
	int	exit_code;
	int	i;
	int	n_flag;

	exit_code = 0;
	i = 0;
	n_flag = 0;
	if (!str_arr)
		return (0);
	if (str_arr[1] && ft_strncmp(str_arr[1], "-n", 2) == 0
		&& ft_strlen(str_arr[1]) == 2)
	{
		n_flag = 1;
		i++;
	}
	while (i++, str_arr[i])
	{
		if (i > 1)
			printf(" ");
		printf("%s", str_arr[i]);
	}
	if (!n_flag)
		printf("\n");
	return (exit_code);
}
