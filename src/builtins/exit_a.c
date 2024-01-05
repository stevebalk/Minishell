/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:43:55 by jopeters          #+#    #+#             */
/*   Updated: 2024/01/05 20:38:04 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/minishell.h"

void	exit_handler(t_ms *ms)
{
	c_red();
	ft_putstr_fd("exit\n",STDERR_FILENO);
	c_reset();
	exit_with_code(ms, ms->last_exit_code);
}

void	builtin_exit(t_ms *ms, char **arr)
{
	c_red();
	fflush(stdout);
	if (get_size_of_array(arr) == 1)
		exit_handler(ms);
	else if (get_size_of_array(arr) == 2)
	{
		if (ft_is_str_num(arr[1]))
		{
			ms->last_exit_code = ft_atoi(arr[1]);
			exit_handler(ms);
		}
		else
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(arr[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			ms->last_exit_code = 255;
			exit_handler(ms);
		}
	}
	ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
	ms->last_exit_code = 1;
	exit_handler(ms);
}
