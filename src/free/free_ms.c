/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ms.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:05:29 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/04 17:17:16 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ms(t_ms *ms)
{
	free_token_list(&(ms->tk));
	free_expander_list(&(ms->exp));
	free_cmd_list(&(ms->cmd));
	if (ms->last_exit_code)
		free(ms->last_exit_code);
	// ft_lstclear(&(ms->envp), ft_lstdelone);
}