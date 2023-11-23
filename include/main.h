/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:56:23 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/23 12:29:56 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libs/libft/include/libft.h"
#include <fcntl.h>
#include <signal.h>

#define FILE_HISTORY "history.txt"
#define MAX_HISTORY 10
#define CLR_SCREEN 0

// contains, the copy of a  export var like >a="huhu"<; the var_name >a<, the raw value >"huhu"< the value witout quotes >huhu< and the value with quotes >"huhu"< 
typedef struct s_var_names
{
	char *raw_copy;
	char *var_name;
	char *raw_value;
	char *value_without_quotes;
	char *value_added_quotes;
	int	has_equal;
} t_var_names;

int		main(int argc, char **argv, char **env);

// Prompt
void	prompt_handler(t_list **history_lst, t_list **env_llst,
			t_list **env_llst_sorted);

// prompt/signal
void	handle_sigint(int sig);

// builtin env
void	show_env_arr(char **env);
void	load_env_to_llst(t_list **env_lst, char **env);
void	show_env_llist(t_list **lst);
void	add_variable_to_llst(t_list **llst, char *var);

// export
void export_arg(t_list **env_llst, t_list **env_llst_sorted, char *str, int str_offset);

void	test_parser_export(t_list **env_llst, t_list **env_llst_sorted,
			char *str);
void	export_single_arg(t_list **env_llst, t_list **env_llst_sorted, char *str);

void show_var_names(t_var_names *var);

// export b
int		check_var_name(char *str);
int		check_first_c(char c);
int		check_other_c(char c);


// unset
void	test_parser_unset(t_list **env_llst, t_list **env_llst_sorted,
			char *str);
t_list	*find_var_in_llst(t_list **llst, char *var);

// Utils
// history
void	history_master(t_list **history_lst);
void	load_history_llst(char *hist_file_name, t_list **history_lst);
void	write_history_llst(char *hist_file_name, t_list **history_lst);
void	show_history_llist(t_list **lst);
void	add_history_llst_to_prompt(t_list **history_lst);
void	limit_history_llst(t_list **history_lst);

//util_lst

void	lst_delete_first(t_list **llist);
void	lst_dealloc(t_list **llist, int free_content);

void	copy_llst(t_list **src_llst, t_list **new_llst);
void	swap_nodes(t_list *a, t_list *b);
void	sort_list(t_list *head);
void	delete_node_from_llst(t_list **head, t_list *nodeToDelete);

void	update_content_in_node(t_list *node, char *new_content);

// util_string

char	*get_string_till_first_symbol(char *str_in, char symbol);
char	*get_string_without_symbols(char *str_in, char symbol);
char	*get_string_with_symbols_at_end_and_front(char *str_in, char symbol);
char	*get_string_from_first_symbol(char *str_in, char symbol);
char	*get_string_from_string(char *str_in);

char	*join_three_string(char *str1, char *str2, char *str3);

int		get_first_symbol_pos(char *str, char symbol);
int		find_newline(char *str);
void	del_first_nl(char *str);
int		has_str_sympbol(char *str, char symbol);

// Colors
void	c_red(void);
void	c_green(void);
void	c_blue(void);
void	c_purple(void);
void	c_yellow(void);
void	c_cyan(void);
void	clear_screen(void);
void	c_reset(void);

// utils dealloc
void	ini_var_names_to_null(t_var_names *var); // XXX muss woanders hin
void	dealloc_var_names(t_var_names *var);


// Jonas Temp
void	show_var_names(t_var_names *var);