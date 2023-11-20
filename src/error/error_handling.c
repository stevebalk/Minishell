/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:17:43 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/20 16:28:58 by sbalk            ###   ########.fr       */
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
	if (tk_head != NULL)
		free_lx(tk_head);
	if (shall_exit && use_errno)
		exit(errno);
	else if (shall_exit)
		exit(EXIT_FAILURE);
}