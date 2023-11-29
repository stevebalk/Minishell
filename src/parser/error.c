/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:29:23 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/29 15:37:39 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unexpected_token(t_ms *ms, char *token_name, int shall_free)
{
	ft_putnstr_fd("minishell: ", 2, 11);
	ft_putnstr_fd("syntax error near unexpected token `", 2, 36);
	ft_putnstr_fd(token_name, 2, ft_strlen(token_name));
	ft_putnstr_fd("'", 2, 1);
	ms->last_exit_code = "127";
	if (shall_free)
	{
		free_lx(ms->tk);
		ms->tk = NULL;
		free_cmd_exept_here_doc(ms->cmd);
		ms->cmd = NULL;
	}
	return (-1);
}
