/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_logic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:14:36 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/28 14:52:31 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Creates and sets the token content/string */
static void	create_token_content(t_token *token, char *str,
								int size, t_token *tk_head)
{
	token->content = malloc((size + 1) * sizeof(char));
	if (token->content == NULL)
		lx_error(tk_head, "Malloc failed", 1, 1);
	ft_strlcpy(token->content, str, size + 1);
}

// /* Search for matching quote. If it doesn't find one it
// throws an error and exits the shell */
// static int	get_quote_length(char *str, t_token *tk_head)
// {
// 	int		ret;
// 	char	quote;

// 	ret = 1;
// 	quote = *str;
// 	while (str[ret] != '\0')
// 	{
// 		if (str[ret] == quote)
// 			return (ret + 1);
// 		ret++;
// 	}
// 	lx_error(tk_head, "No matching quote", 1, 0);
// 	return (ret);
// }

/* Checks which metacharacter it is and sets the 
token type accordingly. Returns token string length */
int	set_special_token(char *str, t_token *token, t_token *tk_head)
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
	else if (ft_strncmp(str, ">", 1) == 0)
		token->type = TOKEN_REDIRECT;
	else if (ft_strncmp(str, "|", 1) == 0)
		token->type = TOKEN_PIPE;
	create_token_content(token, str, ret, tk_head);
	return (ret);
}

/* Set a word token until it hits a whitespace, quote
metacharacter or a newline */
int	set_word_token(char *str, t_token *token, t_token *tk_head)
{
	int		length;
	char	quote;

	quote = 0;
	length = 0;
	while (str[length] != '\0' && !ft_strchr(TOKEN_TYPES, str[length]))
	{
		if ((str[length] == '\'' || str[length] == '\"') && !quote)
			quote = str[length];
		else if (str[length] == quote)
			quote = 0;
		if (quote == 0 && str[length] == ' ')
			break ;
		length++;
	}
	token->content = malloc((length + 1) * sizeof(char));
	if (token->content == NULL)
		lx_error(tk_head, "Malloc failed", 1, 1);
	ft_strlcpy(token->content, str, length + 1);
	token->type = TOKEN_WORD;
	return (length);
}
