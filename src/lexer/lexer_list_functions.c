/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:02:12 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/05 18:05:30 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Returns a pointer to the last token node in the
given list */
t_token	*get_last_token(t_token *token)
{
	while (token->next != NULL)
		token = token->next;
	return (token);
}

/* Creates initilized token if successful */
t_token	*create_token(t_ms *ms)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	check_if_malloc_failed((void *)token, ms);
	token->next = NULL;
	token->prev = NULL;
	token->type = TOKEN_EOF;
	token->content = NULL;
	return (token);
}

/* Creates a new empty token and appends it to
the linked list. If there is no head token it
will assignes the token as head */
t_token	*token_list_append(t_ms *ms)
{
	t_token	*cur;

	if (ms->tk == NULL)
	{
		ms->tk = create_token(ms);
		return (ms->tk);
	}
	else
	{
		cur = ms->tk;
		while (cur->next != NULL)
			cur = cur->next;
		cur->next = create_token(ms);
		cur->next->prev = cur;
	}
	return (cur->next);
}
