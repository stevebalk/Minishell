/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:56:23 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/13 12:25:34 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "../libs/libft/include/libft.h"
#include <fcntl.h>

#define FILE_HISTORY "history.txt"

// typedef struct s_history
// {
//     char *line;
//     struct s_history *next;
// } t_history;


int	main(void);

// Prompt
void prompt_handler(t_list **history_lst);
char *prompt_read(char *in);

// Utils
// history
void load_history_llst(char *hist_file_name, t_list **history_lst);
void write_history_llst(char *hist_file_name, t_list **history_lst);
void show_history_llist(t_list **lst);
void add_history_llst_to_prompt(t_list **history_lst);



// Colors
void c_red(void);
void c_green(void);
void c_blue(void);
void c_purple(void);
void c_yellow(void);
void c_cyan(void);
void clear_screen(void);
void c_reset(void);
