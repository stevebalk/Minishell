/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:03:32 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/07 01:26:09 by jonas            ###   ########.fr       */
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
void show_redir(t_cmd *cmd)
{
	int i;
	i = -1;
	while(i++, cmd->redirs)
	{
		c_green(); printf("\tRedir: %i  >%s<  Type: %i  \n ", i, cmd->redirs->target, cmd->redirs->type);	
		cmd->redirs = cmd->redirs->next;
	}
}

void show_command_llst(t_ms *ms)
{
	c_yellow(); printf("show_command_llst ()\n"); c_reset();

	t_cmd	*tmp_cmd;
	int		i;
	int		i2;

	i = 0;
	
	tmp_cmd = ms->cmd;
	c_purple();
	while(tmp_cmd)
	{
		i2 = -1;
		while(tmp_cmd->argv[++i2])
			printf("\tCommand Nr: %i   argv[%i] >%s< \n", i, i2, tmp_cmd->argv[i2]);
		show_redir(tmp_cmd);

		tmp_cmd = tmp_cmd->next;
	}
	c_red(); printf("~show_command_llst ()\n"); c_reset();

}

void test_command(t_ms *ms)
{
	c_yellow(); printf("test command ()\n"); c_reset();

	ms->cmd = create_cmd_node(ms);
	ms->cmd->argv = ft_split("ls -la", ' ');
	ms->cmd->redirs = append_redir_node(ms, ms->cmd);
	ms->cmd->redirs->target = join_three_string("input1.txt", "", "");
	ms->cmd->redirs->type = 1; // ??? kein Plan was da rein muss
	
	// ms->cmd = ms->cmd->next;
	// ms->cmd = append_cmd_node(ms);
	// ms->cmd->argv = ft_split("grep \"huhu\"", ' ');
	// ms->cmd->redirs = append_redir_node(ms, ms->cmd);
	// ms->cmd->redirs->target = join_three_string("input2.txt", "", "");
	// ms->cmd->redirs->type = 1; // ??? kein Plan was da rein muss

	
	show_command_llst(ms);
	
	c_red(); printf("~test command ()\n"); c_reset();

}

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


	test_command(&ms);

//	prompt_handler(&ms);
	
	
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
