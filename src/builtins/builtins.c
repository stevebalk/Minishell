/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:20:53 by jopeters          #+#    #+#             */
/*   Updated: 2024/01/04 13:19:49 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/minishell.h"

/* return 1 if the cmd_in comming from the prompt has the same length 
and characters of cmd_manual */
static int	builtin_compare(char *cmd_in, char *cmd_manual)
{
	int	strlen_cmd_in;
	int	strlen_cmd_manual;

	strlen_cmd_in = ft_strlen(cmd_in);
	strlen_cmd_manual = ft_strlen(cmd_manual);
	if (ft_strncmp(cmd_in, cmd_manual, strlen_cmd_manual) == 0 &&
		strlen_cmd_in == strlen_cmd_manual)
		return (1);
	return (0);
}

// executes the builtins and return the exit_code of builtin
int	builtin_master(t_ms *ms, char **cmd_arr)
{
	int		exit_code;

	exit_code = 0;
	if (builtin_compare(cmd_arr[0], "cd"))
		exit_code = builtin_cd(ms, NULL, NULL, cmd_arr[1]);
	if (builtin_compare(cmd_arr[0], "echo"))
		exit_code = builtin_echo(cmd_arr);
	if (builtin_compare(cmd_arr[0], "env"))
		exit_code = show_env_llist(&ms->env_llst);
	if (builtin_compare(cmd_arr[0], "export"))
		exit_code = exp_arg_arr(&ms->env_llst, &ms->env_llst_sorted, cmd_arr);
	if (builtin_compare(cmd_arr[0], "pwd"))
		exit_code = builtin_pwd(&ms->env_llst, &ms->env_llst_sorted, 1);
	if (builtin_compare(cmd_arr[0], "unset"))
		exit_code = builtin_unset(ms, cmd_arr);
	if (builtin_compare(cmd_arr[0], "exit"))
		exit_handler(ms);
	return (exit_code);
}