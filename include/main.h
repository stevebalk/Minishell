/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:56:23 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/10 12:15:54 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../libs/readline/readline.h"

int	main(void);


// Prompt
char *prompt(char *in);

// Utils
// Colors
void c_red(void);
void c_green(void);
void c_blue(void);
void c_purple(void);
void c_yellow(void);
void c_cyan(void);
void clear_screen(void);
void c_reset(void);
