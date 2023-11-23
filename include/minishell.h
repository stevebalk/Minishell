/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:02:49 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/23 11:34:03 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include "libft.h"
#include "lexer.h"
#include "expander.h"
#include "parser.h"

/* Main Minishell struct */
typedef struct	s_ms
{
	t_token		*tk;
	t_cmd		*cmd;
	t_list		*envp;
	t_expand	*exp;
	char		*last_exit_code;
}				t_ms;

/* Error handling */

void	check_if_malloc_failed(void *src, t_ms *ms);

// void	ms_error(t_ms *ms, char *msg, int shall_exit, int use_errno);
void	ms_error(t_ms *ms, char *msg, int shall_exit, int use_errno);
void	lx_error(t_token *tk_head, char *msg, int shall_exit, int use_errno);
void	parse_error(t_parse *parse, char *msg, int shall_exit, int use_errno);

/* Freeing stuff */
void	free_lx(t_token *token);
void	free_redir(t_redir *redir);
void	free_cmd(t_cmd *cmd);
void	free_exp(t_expand *exp);

#endif