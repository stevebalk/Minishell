/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:16:37 by jopeters          #+#    #+#             */
/*   Updated: 2024/01/04 11:53:56 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../include/main.h"
#include "../../include/minishell.h"
#include "../include/builtins.h"

/* DEBUG DELETE LATER */
void	print_lexer_struct(t_token *tk)
{
	while (tk != NULL)
	{
		printf("Type: %i\n", tk->type);
		printf("String: %s\n", tk->content);
		printf("\n");
		tk = tk->next;
	}
}

// copy from steves main after first merge
void quick_lexer(t_ms *ms, char *prompt_in)	
{
	// ACHTUNG Hier sind noch memory leaks!!! 
	//t_ms	ms;
	c_yellow(); printf("quick_lexer() >"); 
	c_green(); printf("%s", prompt_in);
	c_yellow(); printf("<\n"); c_reset();

	//init_ms(ms);
	ms->last_exit_code = 127;
	lex(prompt_in, ms); // Hier den String angeben der getestet werden soll
	c_yellow(); printf("DEBUG before expand\n"); c_blue();
	
	print_lexer_struct(ms->tk); // DEBUG before expand
	expand(ms);
	
	c_yellow(); printf("DEBUG after expand\n"); c_blue();
	
	print_lexer_struct(ms->tk); // DEBUG after expand
	
	c_reset();
	//free_ms(&ms);
}

void	prompt_handler(t_ms *ms)
{
	char	*prompt_in;

	prompt_in = NULL;
	if (CLR_SCREEN == 1)
		clear_screen();
	while (1)
	{
		prompt_in = readline("\033[0;35mmini(s)hell\033[0;33m >> \033[0;36m");

		tty_set_flag(TTY_OMIT_LF, 0);
		if (!is_valid_quote_count(prompt_in))
		{
			free_n_null((void **)&prompt_in);
			continue ;
		}
		if (prompt_in != NULL)
		{
			if (ft_strlen(prompt_in) > 0)
			{
				clear_history();
				add_variable_to_llst(&ms->hist_llst, prompt_in);
				lex(prompt_in, ms);
				expand(ms);
				parse(ms);
				executer(ms);
				limit_history_llst(&ms->hist_llst);
				write_history_llst(ms->tmp_history_folder_file, &ms->hist_llst);
				add_history_llst_to_prompt(&ms->hist_llst);
			}
		}
		else
		{
			c_red();
			write(STDERR_FILENO, "exit\n", 5);
			free_n_null((void **)&prompt_in);
			break ;
		}
		free_n_null((void **)&prompt_in);
	}
}

/*
BASH
	Control + C		--> Closes the actual process and returns to BASH
	Control + D		--> types exit (without ^D) and closes BASH
*/