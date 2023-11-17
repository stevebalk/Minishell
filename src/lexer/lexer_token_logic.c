/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_logic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:14:36 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/17 14:51:19 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

/* Creates and sets the token content/string */
static void	create_token_content(t_token *token, char *str,
								int size, t_token *lx)
{
	token->content = malloc((size + 1) * sizeof(char));
	if (token->content == NULL)
		lx_error(lx, "Malloc failed", 1, 1);
	ft_strlcpy(token->content, str, size + 1);
}

/* Search for matching quote. If it doesn't find one it
throws an error and exits the shell */
static int	get_quote_length(char *str, t_token *lx)
{
	int		ret;
	char	quote;

	ret = 1;
	quote = *str;
	while (str[ret] != '\0')
	{
		if (str[ret] == quote)
			return (ret + 1);
		ret++;
	}
	lx_error(lx, "No matching quote", 1, 0);
	return (ret);
}

/* Checks which metacharacter it is and sets the 
token type accordingly. Returns token string length */
int	set_special_token(char *str, t_token *token, t_token *lx)
{
	int	ret;

	ret = 1;
	if (ft_strncmp(str, "<<", 2) == 0)
	{
		token->type = TOKEN_HERE_DOC;
		ret++;
	}
	else if (ft_strncmp(str, "<", 1) == 0)
		token->type = TOKEN_INFILE;
	else if (ft_strncmp(str, ">>", 2) == 0)
	{
		token->type = TOKEN_REDIRECT_APPEND;
		ret++;
	}
	else if(ft_strncmp(str, ">", 1) == 0)
		token->type = TOKEN_REDIRECT;
	else if (ft_strncmp(str, "|", 1) == 0)
		token->type = TOKEN_PIPE;
	create_token_content(token, str, ret, lx);
	return (ret);
}

/* Checks if the given char would match type WORD and
set the join flag accordingly */
void	set_join_flag(char *str, t_token *token)
{
	if (ft_is_space(str) || ft_strchr(TOKEN_TYPES, *str))
		token->join = 0;
	else
		token->join = 1;
}

/* Set a word token until the matching quote, including quotes */
int	set_word_quote_token(char *str, t_token *token, t_token *lx)
{
	int		length;

	length = 0;
	length = get_quote_length(str, lx);
	token->content = malloc((length + 1) * sizeof(char));
	if (token->content == NULL)
		lx_error(lx, "Malloc failed", 1, 1);
	ft_strlcpy(token->content, str, length + 1);
	token->type = TOKEN_WORD;
	set_join_flag(str + length, token);
	return (length);
}

/* Set a word token until it hits a whitespace, quote
metacharacter or a newline */
int	set_word_token(char *str, t_token *token, t_token *lx)
{
	int length;

	length = 0;
	while (str[length] != '\0'
			&& str[length] != '\''
			&& str[length] != '\"'
			&& !ft_is_space(str + length)
			&& !ft_strchr(TOKEN_TYPES, str[length]))
		length++;
	token->content = malloc((length + 1) * sizeof(char));
	if (token->content == NULL)
		lx_error(lx, "Malloc failed", 1, 1);
	ft_strlcpy(token->content, str, length + 1);
	token->type = TOKEN_WORD;
	set_join_flag(str + length, token);
	return (length);
}
