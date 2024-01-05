/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:43:55 by jopeters          #+#    #+#             */
/*   Updated: 2024/01/05 14:32:08 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/minishell.h"

static	int	len_array(char **arr)
{
	int	count;

	count = 0;
	while (arr[count])
		count++;
	return (count);
}

void	builtin_exit(t_ms *ms, char **arr)
{
	if (len_array(arr) == 1)
		exit_handler(ms);
	else if (len_array(arr) == 2)
	{
		if (ft_is_str_num(arr[1]))
		{
			ms->last_exit_code = ft_atoi(arr[1]);
			exit_handler(ms);
		}
		else
		{
			c_red();
			fflush(stdout);
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(arr[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			c_reset();
		}
	}
	else
		write(STDERR_FILENO, "minishell: exit: too many arguments\n", 36);
}

void	exit_handler(t_ms *ms)
{
	int	exit_code;

	exit_code = ms->last_exit_code;
	c_red();
	write(STDERR_FILENO, "exit\n", 5);
	c_cyan();
	c_reset();
	free_ms(ms);
	printf("last exit code: %i\n", exit_code);
	exit(exit_code);
}
