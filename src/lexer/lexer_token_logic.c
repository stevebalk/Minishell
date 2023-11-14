/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_logic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:14:36 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/14 14:24:47 by sbalk            ###   ########.fr       */
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
static int	get_matching_quote_len(char *str, t_token *lx)
{
	char	quote;
	int		ret;

	quote = *str;
	ret = 1;
	while (str[ret] != '\0')
	{
		if (str[ret] == quote)
			return (ret + 1);
		ret++;
	}
	lx_error(lx, "No matching quote", 1, 0);
	return (ret);
}

/* Checks which special character it is and sets the 
token type accordingly */
int	set_special_token(char *str, t_token *token, t_token *lx)
{
	int	ret;

	ret = 1;
	if (str[0] == '=')
		token->type = TOKEN_ASSIGN;
	if (str[0] == '<')
		token->type = TOKEN_INFILE;
	if (str[1] == '<' && token->type == TOKEN_INFILE)
	{
		token->type = TOKEN_HERE_DOC;
		ret++;
	}
	if (str[0] == '>')
		token->type = TOKEN_REDIRECT;
	if (str[1] == '>' && token->type == TOKEN_REDIRECT)
	{
		token->type = TOKEN_REDIRECT_APPEND;
		ret++;
	}
	if (str[0] == '|')
		token->type = TOKEN_PIPE;
	create_token_content(token, str, ret, lx);
	return (ret);
}

/* Create a word token until it hits a whitespace */
int	set_word_token(char *str, t_token *token, t_token *lx)
{
	int	ret;

	ret = 0;
	while (str[ret] != '\0')
	{
		if (str[ret] == '\'' || str[ret] == '\"')
		{
			ret += get_matching_quote_len(str + ret, lx);
			continue ;
		}
		else if (ft_is_space(str + ret) || ft_strchr(TOKEN_TYPES, str[ret]))
			break ;
		ret++;
	}
	token->type = TOKEN_WORD;
	create_token_content(token, str, ret, lx);
	return (ret);
}
