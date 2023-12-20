/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ms.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:05:29 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/20 14:30:02 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Free the ms struct everything will be NULLed */
void	free_ms(t_ms *ms)
{
	if (!ms)
		return ;
	free_token_list(&(ms->tk));
	free_expander_list(&(ms->exp));
	free_cmd_list(&(ms->cmd));
	if (ms->last_exit_code)
		free_n_null((void **)&ms->last_exit_code);
	if (ms->path_arr)
		ft_free_array((void **)ms->path_arr);
	if (ms->home_dir)
		free_n_null((void **)&ms->home_dir);
	close(ms->fd_stdin);
	close(ms->fd_stdout);

	lst_dealloc(&ms->hist_llst, 1);
	lst_dealloc(&ms->env_llst, 1);
	lst_dealloc(&ms->env_llst_sorted, 1);
}
