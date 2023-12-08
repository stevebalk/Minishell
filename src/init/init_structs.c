/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:25:47 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/08 15:44:05 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_ms(t_ms *ms)
{
	ms->cmd = NULL;
	ms->envp = NULL;
	ms->exp = NULL;
	ms->last_exit_code = NULL;
	ms->tk = NULL;
	ms->unexpected_token = NULL;

	ms->env_llst = NULL;
	ms->env_llst_sorted = NULL;
	ms->hist_llst = NULL;
}
