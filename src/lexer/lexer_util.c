/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:02:12 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/17 14:39:00 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

t_token *get_last_token(t_token *lx)
{
	while (lx->next != NULL)
		lx = lx->next;
	return (lx);
}

/* Free linked token list. Starting at given node */
void	free_lx(t_token *token)
{
	t_token	*cur;
	t_token	*next;

	cur = token;
	while (cur != NULL)
	{
		next = cur->next;
		if (cur->content != NULL)
			free(cur->content);
		free(cur);
		cur = next;
	}
}

void	lx_error(t_token *lx, char *msg, int shall_exit, int use_errno)
{
	if (msg)
		perror(msg);
	if (lx != NULL)
		free_lx(lx);
	if (shall_exit && use_errno)
		exit(errno);
	else if (shall_exit)
		exit(EXIT_FAILURE);
}

/* Creates initilized token if successful */
t_token	*create_token(t_token *lx)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		lx_error(lx, "Malloc failed", 1, 1);
	token->next = NULL;
	token->prev = NULL;
	token->type = TOKEN_EOF;
	token->join = 0;
	token->content = NULL;
	return (token);
}
