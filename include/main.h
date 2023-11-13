/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:56:23 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/13 15:26:10 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "../libs/libft/include/libft.h"
#include <fcntl.h>

#define FILE_HISTORY "history.txt"
#define MAX_HISTORY 5


int	main(void);

// Prompt
void prompt_handler(t_list **history_lst);


void del_first_nl(char *str);
void lst_delete_first(t_list **llist);

// Utils
// history
int find_newline(char *str);
void load_history_llst(char *hist_file_name, t_list **history_lst);
void write_history_llst(char *hist_file_name, t_list **history_lst);
void show_history_llist(t_list **lst);
void add_history_llst_to_prompt(t_list **history_lst);
void limit_history_llst(t_list **history_lst);



// Colors
void c_red(void);
void c_green(void);
void c_blue(void);
void c_purple(void);
void c_yellow(void);
void c_cyan(void);
void clear_screen(void);
void c_reset(void);
