/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:29:23 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/21 15:24:12 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Prints that an unexpected token appered, also frees the cmd list
except heredocs if shall_free is set */
int	unexpected_token(t_ms *ms, char *token_name, int shall_free)
{
	ft_putnstr_fd("minishell: ", 2, 11);
	ft_putnstr_fd("syntax error near unexpected token `", 2, 36);
	ft_putnstr_fd(token_name, 2, ft_strlen(token_name));
	ft_putnstr_fd("'\n", 2, 2);
	ms->last_exit_code = 2;
	if (shall_free)
	{
		free_token_list(&(ms->tk));
		free_cmd_list_exept_here_doc(&(ms->cmd));
	}
	return (-1);
}
