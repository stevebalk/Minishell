/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:01:28 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/09 23:43:36 by sbalk            ###   ########.fr       */
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
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_INFILE,
	TOKEN_HERE_DOC,
	TOKEN_VARIABLE,
	TOKEN_ASSIGN,
	TOKEN_EOF
}		e_token_type;

// Struct for tokens
typedef struct	s_token
{
	e_token_type	type;
	char			*str;
	struct s_token	*next;
}				t_token;

# define TOKEN_TYPES	"|<>$="

#endif
