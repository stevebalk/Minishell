/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:03:32 by sbalk             #+#    #+#             */
/*   Updated: 2024/01/08 13:34:26 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ini_env_history_etc(t_ms *ms, char **env)
{
	load_env_to_llst(&ms->env_llst, env);
	copy_llst(&ms->env_llst, &ms->env_llst_sorted);
	copy_env_home_to_ms_struct(ms);
	copy_path_to_ms_struct(ms);
	sort_list(ms->env_llst_sorted);
	set_history_path(ms);
	history_master(ms);
	add_shell_level(&ms->env_llst, &ms->env_llst_sorted);
	set_shell_var_to_pwd(&ms->env_llst, &ms->env_llst_sorted);
}

int	main(int argc, char **argv, char **env)
{
	t_ms	ms;

	(void) argc;
	(void) argv;
	init_ms(&ms);
	tty_setup();
	if (SHOW_LOGO)
		intro3();
	ini_env_history_etc(&ms, env);
	prompt_handler(&ms);
	exit_handler(&ms);
	return (EXIT_SUCCESS);
}
