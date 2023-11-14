/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:56:23 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/14 16:04:58 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "../libs/libft/include/libft.h"
#include <fcntl.h>

#define FILE_HISTORY "history.txt"
#define MAX_HISTORY 10
#define CLR_SCREEN 1


int	main(int argc, char **argv, char **env);

// Prompt
void prompt_handler(t_list **history_lst);

// builtin env
void show_env_arr(char **env);
void load_env_to_llst(t_list **env_lst, char **env);
void show_env_llist(t_list **lst);

void print_alphabetical(t_list **lst);
char *get_alphabetical_entry(t_list **lst, char c);


// Utils
// history
void history_master(t_list **history_lst);
void load_history_llst(char *hist_file_name, t_list **history_lst);
void write_history_llst(char *hist_file_name, t_list **history_lst);
void show_history_llist(t_list **lst);
void add_history_llst_to_prompt(t_list **history_lst);
void limit_history_llst(t_list **history_lst);

//util_lst
int find_newline(char *str);
void del_first_nl(char *str);
void lst_delete_first(t_list **llist);
void lst_dealloc(t_list **llist);

void copy_llst(t_list **src_llst, t_list **new_llst);
void swapNodes(t_list *a, t_list *b);
void sortList(t_list *head);


// Colors
void c_red(void);
void c_green(void);
void c_blue(void);
void c_purple(void);
void c_yellow(void);
void c_cyan(void);
void clear_screen(void);
void c_reset(void);
