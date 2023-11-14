/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:01:28 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/14 14:17:48 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "../libs/libft/include/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>


// Enum for token types
/*
WORD			= "ALNUM STRING" or "/" or "."
PIPE			= |
REDIRECT		= >
REDIRECT_APPEND	= >>
INFILE			= <
HERE_DOC		= <<
ASSIGN			= =
TOKEN_EOF		= NULL
*/
typedef	enum
{
	TOKEN_WORD				= 0,
	TOKEN_PIPE				= 1,
	TOKEN_REDIRECT			= 2,
	TOKEN_REDIRECT_APPEND	= 3,
	TOKEN_INFILE			= 4,
	TOKEN_HERE_DOC			= 5,
	TOKEN_VARIABLE			= 6,
	TOKEN_ASSIGN			= 7,
	TOKEN_EOF				= 8
}		e_token_type;

// Struct for tokens
typedef struct	s_token
{
	e_token_type	type;
	char			*content;
	struct s_token	*next;
}				t_token;

# define TOKEN_TYPES	"|<>="

t_token		*create_token(t_token *lx);
void		append_token(t_token *head, t_token *new_token);
void		lx_error(t_token *lx, char *msg, int shall_exit, int use_errno);
int			set_special_token(char *str, t_token *token, t_token *lx);
int			set_word_token(char *str, t_token *token, t_token *lx);
t_token		*lexer(char *str);

#endif
