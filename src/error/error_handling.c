/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:17:43 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/22 14:26:26 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_error(t_parse *parse, char *msg, int shall_exit,
			int use_errno)
{
	if (msg)
		perror(msg);
	if (parse->tk != NULL)
		free_lx(parse->tk);
	if (parse->cmd != NULL)
		free_cmd(parse->cmd);
	if (shall_exit && use_errno)
		exit(errno);
	else if (shall_exit)
		exit(EXIT_FAILURE);
}

void	lx_error(t_token *tk_head, char *msg, int shall_exit, int use_errno)
{
	if (msg)
		perror(msg);
	if (tk_head)
		free_lx(tk_head);
	if (shall_exit && use_errno)
		exit(errno);
	else if (shall_exit)
		exit(EXIT_FAILURE);
}

void	ms_error(t_ms *ms, char *msg, int shall_exit, int use_errno)
{
	if (msg)
		perror(msg);
	if (ms->tk)
		free_lx(ms->tk);
	if (ms->exp)
		free_exp(ms->exp);
	if (shall_exit && use_errno)
		exit(errno);
	else if (shall_exit)
		exit(EXIT_FAILURE);
}
