/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:17:43 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/05 14:55:34 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Frees ms struct, print error msg if given and exits the program
if shall_exit is set */
void	ms_error(t_ms *ms, char *msg, int shall_exit, int use_errno)
{
	if (!ms)
		return ;
	if (msg)
		perror(msg);
	if (ms->tk)
		free_token_list(&(ms->tk));
	if (ms->exp)
		free_expander_list(&(ms->exp));
	if (ms->cmd)
		free_cmd_list(&(ms->cmd));
	if (shall_exit && use_errno)
		exit(errno);
	else if (shall_exit)
		exit(EXIT_FAILURE);
}
