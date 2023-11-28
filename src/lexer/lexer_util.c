/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:02:12 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/28 14:52:45 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_last_token(t_token *token)
{
	while (token->next != NULL)
		token = token->next;
	return (token);
}

/* Creates initilized token if successful */
t_token	*create_token(t_token *tk_head)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		lx_error(tk_head, "Malloc failed", 1, 1);
	token->next = NULL;
	token->prev = NULL;
	token->type = TOKEN_EOF;
	token->content = NULL;
	return (token);
}
