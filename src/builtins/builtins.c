/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:20:53 by jopeters          #+#    #+#             */
/*   Updated: 2023/12/18 16:27:19 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/minishell.h"

void	builtin_master(t_ms *ms, char **cmd_arr)
{
	if (!cmd_arr)
		return ;
		
	if ((ft_strncmp(cmd_arr[0], "cd", 2) == 0) && (ft_strlen(cmd_arr[0]) == 2))
	{
		// CD
	}
	if ((ft_strncmp(cmd_arr[0], "echo", 4) == 0) && (ft_strlen(cmd_arr[0]) == 4))
	{
		// echo
	}
	if ((ft_strncmp(cmd_arr[0], "env", 3) == 0) && (ft_strlen(cmd_arr[0]) == 3))
	{
		// env
	}
	if ((ft_strncmp(cmd_arr[0], "exit", 4) == 0) && (ft_strlen(cmd_arr[0]) == 4))
	{
		// exit
	}
	if ((ft_strncmp(cmd_arr[0], "pwd", 3) == 0) && (ft_strlen(cmd_arr[0]) == 3))
	{
		// pwd
	}
	if ((ft_strncmp(cmd_arr[0], "unset", 5) == 0) && (ft_strlen(cmd_arr[0]) == 5))
	{
		// unset
	}
	
	
}