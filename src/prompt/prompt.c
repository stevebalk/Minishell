/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:16:37 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/20 15:29:32 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	prompt_handler(t_list **history_lst, t_list **env_llst, t_list **env_llst_sorted)
{
	char	*prompt_in;
	int		count;
	int		hit_sig;

	(void)count;
	(void)history_lst;
	(void)env_llst;
	(void)env_llst_sorted;
	count = 0;
	prompt_in = NULL;
	hit_sig = 0;
	if (CLR_SCREEN == 1)
		clear_screen();

	while(1)
	{
		prompt_in = readline("\001\033[0;31m\002minihell\001\033[0;33m\002>>\001\033[0;36m\002");
		if (prompt_in != NULL || hit_sig == 0)
		{
			hit_sig = 1;
			if (ft_strlen(prompt_in) > 0)
			{
				add_variable_to_llst(history_lst, prompt_in);
				if (ft_strncmp(prompt_in, "exit", 4) == 0)
				{
					free(prompt_in);
					break ;
				}
				test_parser_unset(env_llst, env_llst_sorted, prompt_in);
				test_parser_export(env_llst, env_llst_sorted, prompt_in);
				limit_history_llst(history_lst);
				write_history_llst(FILE_HISTORY, history_lst);
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
			printf("sig == 2 \n");

			c_red(); 

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