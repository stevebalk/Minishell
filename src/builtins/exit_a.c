/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:43:55 by jopeters          #+#    #+#             */
/*   Updated: 2024/01/05 18:05:14 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/minishell.h"

void	exit_handler(t_ms *ms)
{
	int	exit_code;

	exit_code = ms->last_exit_code;
	c_red();
	write(STDERR_FILENO, "exit\n", 5);
	c_cyan();
	c_reset();
	free_ms(ms);
	exit(exit_code);
}

int	builtin_exit(t_ms *ms, char **arr)
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
			return (ms->last_exit_code);
		}
	}
	ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
	ms->last_exit_code = 1;
	return (ms->last_exit_code);
}
