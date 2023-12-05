/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:03:45 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/05 13:15:48 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Frees the given token node and sets it to NULL */
void	free_token(t_token **token)
{
	if (token && *token)
	{
		if ((*token)->content)
			free((*token)->content);
		if ((*token)->next)
			(*token)->next->prev = NULL;
		free(*token);
		*token = NULL;
	}
}

/* Free token node, but not the content pointer and also NULLs it*/
void	free_token_but_not_content(t_token **token)
{
	if (token && *token)
	{
		if ((*token)->next)
			(*token)->next->prev = NULL;
		free(*token);
		*token = NULL;
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
		free_token(&cur);
		cur = next;
	}
	*list = NULL;
}
