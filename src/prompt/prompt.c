/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:16:37 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/29 14:00:48 by jonas            ###   ########.fr       */
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
void quick_lexer(char *prompt_in)	
{
	t_ms	ms;
	c_yellow(); printf("quick_lexer() >"); 
	c_green(); printf("%s", prompt_in);
	c_yellow(); printf("<\n"); c_reset();

	init_ms(&ms);
	ms.last_exit_code = "127";
	ms.tk = lex(prompt_in); // Hier den String angeben der getestet werden soll
	c_yellow(); printf("DEBUG before expand\n"); 
	c_blue();
	print_lexer_struct(ms.tk); // DEBUG before expand
	expand(&ms);
	c_yellow(); printf("DEBUG after expand\n"); 
	c_blue();
	print_lexer_struct(ms.tk); // DEBUG after expand
	c_reset();
	//free_ms(&ms);
}


void	prompt_handler(t_ms *ms)
//void	prompt_handler(t_list **history_lst, t_list **env_llst, t_list **env_llst_sorted)
{
	char	*prompt_in;
	int		count;
	int		hit_sig;

	(void)count;
	// (void)history_lst;
	// (void)env_llst;
	// (void)env_llst_sorted;
	count = 0;
	prompt_in = NULL;
	hit_sig = 0;
	if (CLR_SCREEN == 1)
		clear_screen();
	while (1)
	{
		prompt_in = readline("\001\033[0;31m\002minihell\001\033[0;33m\002>>\001\033[0;36m\002");
		if (prompt_in != NULL || hit_sig == 0)
		{
			hit_sig = 1;
			if (ft_strlen(prompt_in) > 0)
			{
				add_variable_to_llst(&ms->hist_llst, prompt_in);
				if (ft_strncmp(prompt_in, "exit", 4) == 0)
				{
					free(prompt_in);
					break ;
				}
				// test_parser_unset(env_llst, env_llst_sorted, prompt_in);
				// test_parser_export(env_llst, env_llst_sorted, prompt_in);
				quick_lexer(prompt_in);		// copy from steves main after first merge
				c_green(); printf("after quick lexer\n");
				limit_history_llst(&ms->hist_llst);
				write_history_llst(FILE_HISTORY, &ms->hist_llst);
				add_history(prompt_in);
				free(prompt_in);
			}
			else
				free(prompt_in);
		}
		else
		{
			printf("\nprompt_in == NULL\n");
			hit_sig = 1;
			printf("sig == 2 \n");c_red(); 
			free(prompt_in);
			printf("exit\n");
			break ;
		}
		count++;
	}
	c_red();
	printf("~prompt Handler()\n");
}

/*
BASH
	Control + C		--> Closes the actual process and returns to BASH
	Control + D		--> types exit (without ^D) and closes BASH
*/