/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:17:43 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/20 16:04:34 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	parse_error(t_parse parse_head, char *msg, int shall_exit,
// 			int use_errno)
// {
// 	if (msg)
// 		perror(msg);
// 	if (parse_head->tk != NULL)
// 		free_lx(parse_head->tk);
// 	if (parse_head->cmd != NULL)
// 		free_cmd(parse_head->cmd);
// 	if (shall_exit && use_errno)
// 		exit(errno);
// 	else if (shall_exit)
// 		exit(EXIT_FAILURE);
// }

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