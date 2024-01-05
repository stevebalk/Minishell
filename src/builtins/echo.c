/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:43:21 by jonas             #+#    #+#             */
/*   Updated: 2024/01/05 19:27:46 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "minishell.h"

int	builtin_echo(char **str_arr)
{
	size_t	i;
	size_t	n_flag;

	i = 1;
	n_flag = 0;
	while (str_arr && str_arr[i])
	{
		if (ft_strncmp(str_arr[i], "-n", 2) == 0
			&& ft_strlen(str_arr[i]) == 2)
			n_flag = 1;
		else
			break ;
		i++;
	}
	while (str_arr && str_arr[i])
	{
		ft_putstr_fd(str_arr[i], STDOUT_FILENO);
		if (i < get_size_of_array(str_arr) - 1)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (!n_flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
