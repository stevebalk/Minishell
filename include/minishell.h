/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:02:49 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/12 13:27:25 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define READLINE_LIBRARY	// JJJ

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
// # include <readline/history.h>
// # include <readline/readline.h>
# include "../libs/readline/include/readline/history.h"
# include "../libs/readline/include/readline/readline.h"
# include "../libs/libft/include/libft.h"
# include <signal.h>
# include <dirent.h>
# include "lexer.h"
# include "expander.h"
# include "parser.h"
# include "executer.h"
# include "builtins.h"

# define FILE_HISTORY "history.txt"
# define MAX_HISTORY 10
# define CLR_SCREEN 0

/*
⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣶⣶⣤⡀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⣾⣿⣿⣿⣿⣿⡄⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠹⣿⣿⣿⣿⡿⠁⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⠉⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⣰⣿⣿⣿⣦⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⣰⣿⣿⣿⣿⣿⠀⠀⠀⠀
⠀⠀⠀⠀⠀⢰⣿⣿⣿⣿⣿⣿⡀⠀⠀⠀
⠀⠀⠀⠀⢠⣿⣿⣿⣿⡿⣿⣿⣧⣀⠀⠀
⠀⠀⠀⠀⢺⣿⣿⣿⣿⣧⣬⣻⢿⣿⣿⡦
⠀⠀⠀⠀⠀⠙⠻⠿⢿⣿⣿⣿⣿⡏⠛⠁
⠀⠀⠀⣀⠀⠀⠀⠀⠀⠀⣽⣿⡿⠁⠀⠀
⠀⢀⡠⣿⣷⣤⡀⠀⠀⢸⣿⣿⠃⠀⠀⠀
⠰⠿⠿⠿⠿⠿⠇⠀⠠⠿⠿⠏
Minishell
*/

// Enum for token types
/*
WORD			= "ALNUM STRING" or "/" or "."
PIPE			= |
REDIRECT		= >
REDIRECT_APPEND	= >>
INFILE			= <
HERE_DOC		= <<
TOKEN_EOF		= NULL
*/
typedef enum e_token_type
{
	TOKEN_WORD				= 0,
	TOKEN_PIPE				= 1,
	TOKEN_REDIRECT			= 2,
	TOKEN_REDIRECT_APPEND	= 3,
	TOKEN_INFILE			= 4,
	TOKEN_HERE_DOC			= 5,
	TOKEN_VARIABLE			= 6,
	TOKEN_EOF				= 7
}		t_token_type;

/* Main Minishell struct */
typedef struct s_ms
{
	t_token		*tk;
	t_cmd		*cmd;
	t_list		*envp;
	t_expand	*exp;

	t_list		*hist_llst;
	t_list		*env_llst;
	t_list		*env_llst_sorted;

	char		*home_dir;
	char		**path_arr;
	
	char		*last_exit_code;
	int			last_exit_code_int;
	char		*unexpected_token;

}				t_ms;

typedef struct s_cmd_io
{
	char			*input;
	t_token_type	intype;
	int				in_fd;
	char			*output;
	t_token_type	outtype;
	int				out_fd;
}				t_cmd_io;


/* Init */
void		init_ms(t_ms *ms);

/* lexer */
void		lex(char *str, t_ms *ms);
t_token		*create_token(t_ms *ms);
t_token		*get_last_token(t_token *lx);
t_token		*token_list_append(t_ms *ms);
int			set_word_token(char *str, t_token *token, t_ms *ms);
int			set_special_token(char *str, t_token *token, t_ms *ms);

/* EXPANDER */

void		expand(t_ms *ms);
void		check_if_valid_quote_count(t_token *token, t_ms *ms);
t_expand	*create_expand_node(t_ms *ms);
t_expand	*append_chunk(t_ms *ms);
void		append_and_fill_chunk_with_str(t_ms *ms, const char *src,
				size_t len);
void		expand_env_varible(char **str, t_ms *ms, char *prev_quote);
void		append_and_fill_chunk_with_str(t_ms *ms, const char *src,
				size_t len);
void		expand_no_quotes(char **str, t_ms *ms, char *quote);
void		expand_single_quote_content(char **str, t_ms *ms);
void		expand_double_quote_content(char **str, t_ms *ms,
				char *prev_quote);
char		*join_chunks_to_final_word(t_ms *ms);
void		create_empty_string_chunk(t_ms *ms);

/* PARSER */
int			parse(t_ms *ms);
t_cmd		*create_cmd_node(t_ms *ms);
t_cmd		*append_cmd_node(t_ms *ms);
t_redir		*append_redir_node(t_ms *ms, t_cmd *cmd);
t_redir		*create_heredoc_only_redir(t_redir *list);
int			unexpected_token(t_ms *ms, char *token_name, int shall_free);

/* EXECUTER */
int			is_builtin_command(char *str);
void		heredoc(char *delimiter, t_ms *ms);

/* Error handling */

void		check_if_malloc_failed(void *src, t_ms *ms);
void		ms_error(t_ms *ms, char *msg, int shall_exit, int use_errno);

/* Freeing stuff */
void		free_ms(t_ms *ms);
void		free_token(t_token **token);
void		free_token_but_not_content(t_token **token);
void		free_token_list(t_token **token);

void		free_expander_list(t_expand **list);

void		free_cmd_list(t_cmd **cmd);
void		free_cmd_list_exept_here_doc(t_cmd **cmd);
void		free_redir_node(t_redir **node);
void		free_redir_list(t_redir **list);



// Jonas
// Prompt
void	prompt_handler(t_ms *ms);
void	builtin_cd(t_ms *ms, t_list **env_llst, t_list **env_llst_sorted, char *in);
void	test_parser_cd_pwd_home(t_ms *ms, t_list **env_llst, t_list **env_llst_sorted, char *str);
void	test_parser_get_var(t_list **env_llst, t_list **env_llst_sorted, char *str);


// env b
void	copy_path_to_ms_ms_struct(t_ms *ms);
void	copy_env_home_to_ms_struct(t_ms *ms);

// executer
// check_command
char	*check_program_with_path(t_ms *ms, char *prog_name);
#endif