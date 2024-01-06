/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:16:37 by jopeters          #+#    #+#             */
/*   Updated: 2024/01/06 14:58:44 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../include/builtins.h"

static void	process_promt_input(char *prompt_in, t_ms *ms)
{
	clear_history();
	add_variable_to_llst(&ms->hist_llst, prompt_in);
	if (is_valid_quote_count(prompt_in))
	{
		lex(prompt_in, ms);
		expand(ms);
		parse(ms);
		executer(ms);
	}
	limit_history_llst(&ms->hist_llst);
	write_history_llst(ms->tmp_history_folder_file, &ms->hist_llst);
	add_history_llst_to_prompt(&ms->hist_llst);
}

void	prompt_handler(t_ms *ms)
{
	char	*prompt_in;

	while (1)
	{
		prompt_in = readline(PROMPT);
		tty_set_flag(TTY_OMIT_LF, 0);
		if (prompt_in != NULL)
		{
			if (ft_strlen(prompt_in) > 0)
				process_promt_input(prompt_in, ms);
		}
		else
			break ;
		free_n_null((void **)&prompt_in);
	}
}

/*
BASH
	Control + C		--> Closes the actual process and returns to BASH
	Control + D		--> prints exit (without ^D) and closes BASH
*/