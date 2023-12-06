/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:03:32 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/06 17:56:48 by jonas            ###   ########.fr       */
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
	sort_list(ms->env_llst_sorted);
	history_master(&ms->hist_llst);
	add_shell_level(&ms->env_llst, &ms->env_llst_sorted);
}

int	main(int argc, char **argv, char **env)
{
	t_ms	ms;
	c_yellow(); printf("*** main () ***\n"); c_reset();
	init_ms(&ms);
	(void)argc;
	(void)argv;
	(void)env;

	if (!LOGO_ABOVE_PROMPT)
		intro3();
	
	ini_env_history_etc(&ms, env);

	prompt_handler(&ms);
	
	
	free_ms(&ms);
	
	c_red();
	printf("*** ~main () ***\n"); c_reset();
	return (EXIT_SUCCESS);
}

/* ---------- INPUT TEST MAIN ------------- */

// const char *tokenTypeNames[] = {
// 	"WORD",
// 	"PIPE",
// 	"REDIRECT",
// 	"REDIRECT_APPEND",
// 	"INFILE",
// 	"HERE_DOC",
// 	"VARIABLE",
// 	"EOF"
// };

// void prettyPrintCmd(t_cmd *cmd) {
// 	while (cmd != NULL) {
// 		printf("Command:\n");
// 		if (cmd->argv != NULL) {
// 			printf("  Arguments:\n");
// 			char **arg = cmd->argv;
// 			while (*arg != NULL) {
// 				printf("    %s\n", *arg);
// 				arg++;
// 			}
// 		}

// 		if (cmd->redirs != NULL) {
// 			printf("  Redirections:\n");
// 			t_redir *redir = cmd->redirs;
// 			while (redir != NULL) {
// 				printf("    Type: %s, Filename: %s\n", tokenTypeNames[redir->type], redir->target);
// 				redir = redir->next;
// 			}
// 		}

// 		printf("\n");
// 		cmd = cmd->next;
// 	}
// }

// int	main(void)
// {
// 	t_ms	ms;
// 	char teststring[] = "> dsads << infile | < dsd | fdfs>fdsf | fdsf < fdf fggre >f fd | fdsf" ;
// 	lex(teststring, &ms);
// 	expand(&ms);
// 	parse(&ms);
// 	prettyPrintCmd(ms.cmd);
// 	free_ms(&ms);
// }
