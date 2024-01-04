/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:20:53 by jopeters          #+#    #+#             */
/*   Updated: 2024/01/04 12:17:02 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/minishell.h"

static void	exit_handler(t_ms *ms)
{
	c_red();
	write(STDERR_FILENO, "exit\n", 5);
	c_cyan();
	c_reset();
	free_ms(ms);
	exit(0);
}

// executes the builtins and return the exit_code of builtin
int	builtin_master(t_ms *ms, char **cmd_arr)
{
	int		exit_code;
	
	exit_code = 0;
	if ((ft_strncmp(cmd_arr[0], "cd", 2) == 0) && (ft_strlen(cmd_arr[0]) == 2))
		exit_code = builtin_cd(ms, NULL, NULL, cmd_arr[1]);
	if ((ft_strncmp(cmd_arr[0], "echo", 4) == 0) && (ft_strlen(cmd_arr[0]) == 4))
		exit_code = builtin_echo(cmd_arr);
	if ((ft_strncmp(cmd_arr[0], "env", 3) == 0) && (ft_strlen(cmd_arr[0]) == 3))
		exit_code = show_env_llist(&ms->env_llst);
	if ((ft_strncmp(cmd_arr[0], "export", 6) == 0) && (ft_strlen(cmd_arr[0]) == 6))
		exit_code = export_arg_arr(&ms->env_llst, &ms->env_llst_sorted, cmd_arr);
	if ((ft_strncmp(cmd_arr[0], "exit", 4) == 0) && (ft_strlen(cmd_arr[0]) == 4))
		exit_handler(&ms);
	if ((ft_strncmp(cmd_arr[0], "pwd", 3) == 0) && (ft_strlen(cmd_arr[0]) == 3))
		exit_code = builtin_pwd(&ms->env_llst, &ms->env_llst_sorted, 1);
	if ((ft_strncmp(cmd_arr[0], "unset", 5) == 0) && (ft_strlen(cmd_arr[0]) == 5))
		exit_code = builtin_unset(ms, cmd_arr);
	return (exit_code);
}