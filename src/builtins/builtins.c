/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:20:53 by jopeters          #+#    #+#             */
/*   Updated: 2023/12/19 17:31:02 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/minishell.h"

// executes the builtins and return the exit_code of builtin
int	builtin_master(t_ms *ms, char **cmd_arr)
{
	int		exit_code;
	
	exit_code = 0;
		
	if ((ft_strncmp(cmd_arr[0], "cd", 2) == 0) && (ft_strlen(cmd_arr[0]) == 2))
	{
		//printf("CD\n");
		exit_code = builtin_cd(ms, NULL, NULL, cmd_arr[1]);
	}
	if ((ft_strncmp(cmd_arr[0], "echo", 4) == 0) && (ft_strlen(cmd_arr[0]) == 4))
	{
		//printf("echo\n");
		exit_code = builtin_echo(cmd_arr);
	}
	if ((ft_strncmp(cmd_arr[0], "env", 3) == 0) && (ft_strlen(cmd_arr[0]) == 3))
	{
		//printf("env\n");
		exit_code = show_env_llist(&ms->env_llst);
	}
	if ((ft_strncmp(cmd_arr[0], "export", 6) == 0) && (ft_strlen(cmd_arr[0]) == 6))
	{
		//printf("export\n");
		exit_code = export_arg_arr(&ms->env_llst, &ms->env_llst_sorted, cmd_arr);
		//test_parser_export(&ms->env_llst, &ms->env_llst_sorted,cmd_arr[1]);
	}
	if ((ft_strncmp(cmd_arr[0], "exit", 4) == 0) && (ft_strlen(cmd_arr[0]) == 4))
	{
		c_red();printf("exit\n");c_cyan(); printf("todo: free and exit minishell \n"); 
		c_reset();
		free_ms(ms);
		exit(ms->last_exit_code_int);
	}
	if ((ft_strncmp(cmd_arr[0], "pwd", 3) == 0) && (ft_strlen(cmd_arr[0]) == 3))
	{
		//printf("pwd\n");
		exit_code = builtin_pwd(&ms->env_llst, &ms->env_llst_sorted, 1);
	}
	if ((ft_strncmp(cmd_arr[0], "unset", 5) == 0) && (ft_strlen(cmd_arr[0]) == 5))
	{
		//printf("unset\n");
		exit_code = builtin_unset(ms, cmd_arr);
	}
	
	return (exit_code);
}