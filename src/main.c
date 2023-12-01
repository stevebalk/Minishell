/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:12:12 by jopeters          #+#    #+#             */
/*   Updated: 2023/12/01 16:29:16 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../include/minishell.h"
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

void	copy_env_home_to_ms_struct(t_ms *ms)
{
	char	*home_dir;
	c_yellow(); printf("copy_env_home_to_ms_struct()\n"); c_reset();
	home_dir = get_val_of_var(&ms->env_llst, "HOME");
	c_green();printf("home dir >%s<\n", home_dir); c_reset();
	ms->home_dir = join_three_string(home_dir, "", "");
	if (!home_dir)
		free(home_dir);
	c_red(); printf("~copy_env_home_to_ms_struct()\n"); c_reset();

}


void ini_env_history_etc(t_ms *ms, char **env)
{
	load_env_to_llst(&ms->env_llst, env);
	copy_env_home_to_ms_struct(ms);
	copy_llst(&ms->env_llst, &ms->env_llst_sorted);
	history_master(&ms->hist_llst);
}

int	main(int argc, char **argv, char **env)
{
	// t_list	*hist_llst;
	// t_list	*env_llst;
	// t_list	*env_llst_sorted;
	t_ms	ms;

	init_ms(&ms);
	
	(void)argc;
	(void)argv;
	(void)env;

	ini_env_history_etc(&ms, env);
	printf("HOME DIR in MS Struct >%s<\n", ms.home_dir);
	prompt_handler(&ms);
	
	lst_dealloc(&ms.hist_llst, 1);
	lst_dealloc(&ms.env_llst, 1);
	lst_dealloc(&ms.env_llst_sorted, 1);
	//free_ms(&ms);
	
	c_red(); printf("~main ()\n"); c_reset();
	return (EXIT_SUCCESS);
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