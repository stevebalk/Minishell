/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:13:27 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/05 14:54:28 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Checks string and sets the token type accordingly.
Returns length of the token string length */
int	set_token(t_token *token, char *str, t_ms *ms)
{
	int	ret;

	ret = 0;
	if (ft_strchr(TOKEN_TYPES, *str))
		ret += set_special_token(str, token, ms);
	else
		ret += set_word_token(str, token, ms);
	return (ret);
}

/* Takes an input string and breaks it down into tokens.
It creates and sets token paramters based on the given rules*/
void	lex(char *str, t_ms *ms)
{
	t_token	*cur_token;

	if (*str == '\0')
		return ;
	cur_token = NULL;
	while (*str != '\0')
	{
		while (ft_is_space(str))
			str++;
		if (*str == '\0')
			ms->tk = NULL;
		cur_token = token_list_append(ms);
		str += set_token(cur_token, str, ms);
	}
}
