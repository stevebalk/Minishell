/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:17:43 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/04 17:14:38 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	parse_error(t_parse *parse, char *msg, int shall_exit,
// 			int use_errno)
// {
// 	if (msg)
// 		perror(msg);
// 	if (parse->tk != NULL)
// 		free_lx(parse->tk);
// 	if (parse->cmd != NULL)
// 		free_cmd(parse->cmd);
// 	if (shall_exit && use_errno)
// 		exit(errno);
// 	else if (shall_exit)
// 		exit(EXIT_FAILURE);
// }

void	lx_error(t_token *tk_head, char *msg, int shall_exit, int use_errno)
{
	if (msg)
		perror(msg);
	if (tk_head)
		free_token_list(&tk_head);
	if (shall_exit && use_errno)
		exit(errno);
	else if (shall_exit)
		exit(EXIT_FAILURE);
}

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
