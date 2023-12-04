/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:12:12 by jopeters          #+#    #+#             */
/*   Updated: 2023/12/04 16:56:46 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../include/minishell.h"
#include "minishell.h"

/* DEBUG DELETE LATER */
/*
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

void test(t_ms *ms)
{
	(void)ms;
//    printf("PATH : %s\n", getenv("PATH"));
//    printf("HOME : %s\n", getenv("HOME"));
//    printf("ROOT : %s\n", getenv("ROOT"));
//    printf("PWD  : %s\n", getenv("PWD"));

	char *tmp = check_program_with_path(ms, "ls");
	printf("checked prog: %s \n", tmp);
	free(tmp);
}
*/


void ini_env_history_etc(t_ms *ms, char **env)
{
	load_env_to_llst(&ms->env_llst, env);
	copy_env_home_to_ms_struct(ms);
	copy_path_to_ms_ms_struct(ms);
	copy_llst(&ms->env_llst, &ms->env_llst_sorted);
	history_master(&ms->hist_llst);
	add_shell_level(&ms->env_llst, &ms->env_llst_sorted);
}



int	main(int argc, char **argv, char **env)
{
	t_ms	ms;

	init_ms(&ms);
	(void)argc;
	(void)argv;
	(void)env;

	
	ini_env_history_etc(&ms, env);

	prompt_handler(&ms);
	
	
	free_ms(&ms);
	
	c_red();
	printf("~main ()\n"); c_reset();
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