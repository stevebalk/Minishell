/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:20:53 by jopeters          #+#    #+#             */
/*   Updated: 2023/12/18 17:44:16 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/minishell.h"

void	builtin_master(t_ms *ms, char **cmd_arr)
{
	(void) ms;

	if (!cmd_arr)
		return ;
		
	if ((ft_strncmp(cmd_arr[0], "cd", 2) == 0) && (ft_strlen(cmd_arr[0]) == 2))
	{
		//printf("CD\n");
		builtin_cd(ms, NULL, NULL, cmd_arr[1]);
	}
	if ((ft_strncmp(cmd_arr[0], "echo", 4) == 0) && (ft_strlen(cmd_arr[0]) == 4))
	{
		printf("echo\n");
	}
	if ((ft_strncmp(cmd_arr[0], "env", 3) == 0) && (ft_strlen(cmd_arr[0]) == 3))
	{
		//printf("env\n");
		show_env_llist(&ms->env_llst);
	}
	if ((ft_strncmp(cmd_arr[0], "export", 6) == 0) && (ft_strlen(cmd_arr[0]) == 6))
	{
		//printf("export\n");
		test_parser_export(&ms->env_llst, &ms->env_llst_sorted,cmd_arr[1]);
	}
	if ((ft_strncmp(cmd_arr[0], "exit", 4) == 0) && (ft_strlen(cmd_arr[0]) == 4))
	{
		printf("exit\n");
	}
	if ((ft_strncmp(cmd_arr[0], "pwd", 3) == 0) && (ft_strlen(cmd_arr[0]) == 3))
	{
		//printf("pwd\n");
		builtin_pwd(&ms->env_llst, &ms->env_llst_sorted, 1);
	}
	if ((ft_strncmp(cmd_arr[0], "unset", 5) == 0) && (ft_strlen(cmd_arr[0]) == 5))
	{
		printf("unset\n");
	}
	
	
}