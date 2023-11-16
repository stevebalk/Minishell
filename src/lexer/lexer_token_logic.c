/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_logic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:14:36 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/16 19:11:51 by sbalk            ###   ########.fr       */
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
static int	get_quote_string_length(char *str, t_token *lx)
{
	int		ret;
	char	quote;

	ret = 0;
	quote = *str;
	str++;
	while (str[ret] != '\0')
	{
		if (str[ret] == quote)
			return (ret);
		ret++;
	}
	lx_error(lx, "No matching quote", 1, 0);
	return (ret);
}

/* Checks which special character it is and sets the 
token type accordingly. Return token string length */
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

// /* Create a word token until it hits a whitespace */
// int	set_word_token(char *str, t_token *token, t_token *lx)
// {
// 	int	ret;

// 	ret = 0;
// 	while (str[ret] != '\0')
// 	{
// 		if (str[ret] == '\'' || str[ret] == '\"')
// 		{
// 			ret += get_matching_quote_len(str + ret, lx);
// 			continue ;
// 		}
// 		else if (ft_is_space(str + ret) || ft_strchr(TOKEN_TYPES, str[ret]))
// 			break ;
// 		ret++;
// 	}
// 	token->type = TOKEN_WORD;
// 	create_token_content(token, str, ret, lx);
// 	return (ret);
// }

// void	create_word_token(char *str, int length, t_token *lx)
// {
// 	t_token	*cur;
// 	char	*dst;

// 	if (length == 0)
// 		return ;
// 	cur = get_last_token(lx);
// 	cur->next = create_token(lx);
// 	cur = cur->next;
// 	dst = malloc((length + 1) * sizeof(char));
// 	if (dst == NULL)
// 		lx_error(lx, "Malloc failed", 1, 1);
// 	cur->content = ft_strlcpy(dst, str - length, length + 1);
// }

// int	create_quote_word_token(char *str, t_token *lx)
// {
// 	t_token	*cur;
// 	char	quote;
// 	int		length;

// 	cur = get_last_token(lx);
// 	cur->next = create_token(lx);
// 	cur = cur->next;
// 	quote = *str;
// 	if (quote == '\'')
// 		cur->expandable = 0;
// 	else
// 		cur->expandable = 1;
// 	str++;
// 	length = get_matching_quote_len(quote, lx);
// 	cur->content = malloc(length * sizeof(char));
// 	if (cur->content == NULL)
// 		lx_error(lx, "Malloc failed", 1, 1);
// 	cur->content = ft_strlcpy(cur->content, str, length);
// 	return (length);
// }

/* Checks if the given char would match type word and
sets the join flag accordingly */
void	set_join_flag(char *str, t_token *token)
{
	if (ft_is_space(str) || ft_strchr(TOKEN_TYPES, *str))
		token->join = 0;
	else
		token->join = 1;
}

int	set_word_quote_token(char *str, t_token *token, t_token *lx)
{
	char	quote;
	int		length;

	length = 0;
	quote = *str;
	if (quote == '\'')
		token->expandable = 0;
	else
		token->expandable = 1;
	length = get_quote_string_length(str, lx);
	str++;
	token->content = malloc((length + 1) * sizeof(char));
	if (token->content == NULL)
		lx_error(lx, "Malloc failed", 1, 1);
	ft_strlcpy(token->content, str, length + 1);
	token->type = TOKEN_WORD;
	set_join_flag(str + length + 2, token);
	return (length + 2);
}

/* Create a word token until it hits a whitespace */
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
