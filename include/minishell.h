/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:02:49 by sbalk             #+#    #+#             */
/*   Updated: 2024/01/05 17:33:15 by sbalk            ###   ########.fr       */
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
# include <sys/wait.h>
// # include <readline/history.h>
// # include <readline/readline.h>
# include "../libs/readline/include/readline/history.h"
# include "../libs/readline/include/readline/readline.h"
# include "../libs/libft/include/libft.h"
# include <signal.h>
# include <termios.h>
# include <dirent.h>
# include "lexer.h"
# include "expander.h"
# include "parser.h"
# include "executer.h"
# include "builtins.h"
#include <sys/types.h>
#include <sys/stat.h>

# define FILE_HISTORY "history.txt"
# define MAX_HISTORY 10
# define CLR_SCREEN 0
#define LOGO_ABOVE_PROMPT 0

# define TTY_IS_CHILD 0
# define TTY_HEREDOC 1
# define TTY_OMIT_LF 2

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

# define TOKEN_TYPES	"|<>"

// Flags for terminal and signal behavior

# define TTY_IS_CHILD 0
# define TTY_HEREDOC 1
# define TTY_OMIT_LF 2
# define TTY_SIGNAL_QUIT 3
# define TTY_SIGNAL_INT 4

/* Token struct, created by the lexer to
store the tokens used by the parser. */

typedef struct s_token
{
	t_token_type	type;
	char			*content;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

typedef struct s_cmd_io
{
	char				*input;
	t_token_type		intype;
	int					in_fd;
	char				*output;
	t_token_type		outtype;
	int					out_fd;
	char				**command_arr;
	int					is_valid;
	struct s_cmd_io		*next;
}				t_cmd_io;

/* Redirection struct, used by t_cmd to save
redirections in a linked list*/
typedef struct s_redir
{
	t_token_type	type;
	char			*target;
	struct s_redir	*next;
}				t_redir;

/* Parser struct, saves all redirections
and commands */
typedef struct s_cmd
{
	char			**argv;
	t_redir			*redirs;
	struct s_cmd	*next;
}				t_cmd;

/* Main Minishell struct */
typedef struct s_ms
{
	t_token		*tk;
	t_cmd		*cmd;
	t_list		*envp;
	t_expand	*exp;
	t_cmd_io	*cmd_io;
	int			fd_stdin;
	int			fd_stdout;

	t_list		*hist_llst;
	t_list		*env_llst;
	t_list		*env_llst_sorted;

	char		*tmp_history_folder_file;

	char		*home_dir;
	char		**path_arr;
	
	int			last_exit_code;
	char		*unexpected_token;

}				t_ms;

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
int			is_valid_quote_count(char *str);
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
void		executer(t_ms *ms);
// t_cmd_io	*create_cmd_io_node(t_ms *ms);
// t_cmd_io	*cmd_io_append_node(t_ms *ms);
// void		create_cmd_io_list(t_ms *ms);
void		print_file_error(char *msg);
void		print_execution_error(char *path_name, char *msg);
void		print_command_not_found_error(char *cmd);
int			redir_to_io(t_redir *redir, t_cmd_io *io, char *heredoc_str);
int			is_builtin_command(char *str);
int			is_regular_file(const char *path);
char 		*heredoc(char *delimiter, t_ms *ms, int *is_valid);

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
t_cmd		*free_cmd_head(t_cmd **list);
void		free_redir_node(t_redir **node);
void		free_redir_list(t_redir **list);
void		free_cmd_io_list(t_cmd_io **list);

void		exit_with_code(t_ms *ms, int exit_code);

/* Utils */
size_t		get_size_of_array(char **arr);

// Jonas
// Prompt
void	prompt_handler(t_ms *ms);
int		builtin_cd(t_ms *ms, char **argv);
void	test_parser_cd_pwd_home(t_ms *ms, t_list **env_llst, t_list **env_llst_sorted, char *str);
void	test_parser_get_var(t_list **env_llst, t_list **env_llst_sorted, char *str);

int		builtin_master(t_ms *ms, char **cmd_arr);
int		builtin_unset(t_ms *ms, char **arr);
void	exit_handler(t_ms *ms);
int		builtin_exit(t_ms *ms, char **arr);

void	history_master(t_ms *ms);
void	set_history_path(t_ms *ms);


// env b
void	copy_path_to_ms_struct(t_ms *ms);
void	copy_env_home_to_ms_struct(t_ms *ms);
char 	**copy_llst_to_char_arr(t_list **llst, t_ms *ms);


// executer
// check_command
char	*check_program_with_path(t_ms *ms, char *prog_name);

// TTY and signal handling
void	tty_setup(void);
void	tty_enter(int is_child);
int		tty_get_flag(unsigned int index);
void	tty_set_flag(unsigned int index, int enable);
void	tty_reset_flags(void);
void	signal_handler(int sig);
void	signal_handler_child(int sig);

#endif