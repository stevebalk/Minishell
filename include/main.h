/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:56:23 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/13 10:54:41 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "../libs/libft/include/libft.h"
#include <fcntl.h>

// typedef struct s_history
// {
//     char *line;
//     struct s_history *next;
// } t_history;


int	main(void);

// Prompt
void prompt_handler(void);
char *prompt_read(char *in);

// Utils
// history
void load_history(int fd, t_list **history_lst);
void show_history_list(t_list **lst);
void add_history_llst_to_prompt(t_list **history_lst);
//void	write_history(t_history *history, int fd);

// Colors
void c_red(void);
void c_green(void);
void c_blue(void);
void c_purple(void);
void c_yellow(void);
void c_cyan(void);
void clear_screen(void);
void c_reset(void);
