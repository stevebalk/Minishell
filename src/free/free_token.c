/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:03:45 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/04 17:04:04 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_token *token)
{
	if (token)
	{
		if (token->content)
			free(token->content);
		if (token->next)
			token->next->prev = NULL;
		free(token);
	}
}

void	free_token_but_not_content(t_token *token)
{
	if (token)
	{
		if (token->next)
			token->next->prev = NULL;
		free(token);
	}
}

/* Free linked token list. Starting at given node */
void	free_token_list(t_token **list)
{
	t_token	*cur;
	t_token	*next;

	if (list == NULL || *list == NULL)
		return ;
	cur = *list;
	while (cur != NULL)
	{
		next = cur->next;
		free_token(cur);
		cur = next;
	}
	*list = NULL;
}
