/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ms.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:05:29 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/05 12:17:31 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Free the ms struct everything will be NULLed */
void	free_ms(t_ms *ms)
{
	free_token_list(&(ms->tk));
	free_expander_list(&(ms->exp));
	free_cmd_list(&(ms->cmd));
	if (ms->last_exit_code)
		free(ms->last_exit_code);
}
