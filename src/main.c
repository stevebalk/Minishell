/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:12:12 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/29 12:53:21 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "minishell.h"

// /* DEBUG DELETE LATER */
// void	print_lexer_struct(t_token *tk)
// {
// 	while (tk != NULL)
// 	{
// 		printf("Type: %i\n", tk->type);
// 		printf("String: %s\n", tk->content);
// 		printf("\n");
// 		tk = tk->next;
// 	}
// }

int	main(int argc, char **argv, char **env)
{
	t_list	*hist_llst;
	t_list	*env_llst;
	t_list	*env_llst_sorted;

	hist_llst = NULL;
	env_llst = NULL;
	env_llst_sorted = NULL;
	(void)argc;
	(void)argv;
	(void)env;
	(void)hist_llst;

	load_env_to_llst(&env_llst, env);
	copy_llst(&env_llst, &env_llst_sorted);
	
	history_master(&hist_llst);
	prompt_handler(&hist_llst, &env_llst, &env_llst_sorted);
	
	lst_dealloc(&hist_llst, 1);
	lst_dealloc(&env_llst, 1);
	lst_dealloc(&env_llst_sorted, 1);
	c_red();
	printf("~main ()\n");
	c_reset();
	return (0);
}


/*
int	main(int argc, char **argv)
{
	t_ms	ms;

	init_ms(&ms);
	ms.last_exit_code = "127";
	ms.tk = lex(*SOME_STRING); // Hier den String angeben der getestet werden soll
	print_lexer_struct(ms.tk); // DEBUG before expand
	expand(&ms);
	print_lexer_struct(ms.tk); // DEBUG after expand
	free_ms(&ms);
}
*/
	// char *args[] = {NULL, NULL, NULL};
	// args[0] = ms.tk->content;
	// args[1] = ms.tk->next->content;
	// execv("/bin/ls", args);
	// perror("execv");