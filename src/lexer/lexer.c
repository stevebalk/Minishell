/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:13:27 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/28 14:51:38 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Creates a new empty token and appends it to
the linked list. If there is no head token it
will assignes the token as head */
t_token	*token_list_append(t_token **head)
{
	t_token	*cur;

	if (*head == NULL)
	{
		*head = create_token(*head);
		return (*head);
	}
	else
	{
		cur = *head;
		while (cur->next != NULL)
			cur = cur->next;
		cur->next = create_token(*head);
		cur->next->prev = cur;
	}
	return (cur->next);
}

/* Checks string and sets the token type accordingly.
Returns length of the token string length */
int	set_token(t_token *token, char *str, t_token *lx)
{
	int	ret;

	ret = 0;
	if (ft_strchr(TOKEN_TYPES, *str))
		ret += set_special_token(str, token, lx);
	else
		ret += set_word_token(str, token, lx);
	return (ret);
}

/* Takes an input string and breaks it down into tokens.
It creates and sets tokenparamters based on the given rules*/
t_token	*lexer(char *str)
{
	t_token	*head;
	t_token	*cur_token;

	if (*str == '\0')
		return (NULL);
	head = NULL;
	cur_token = NULL;
	while (*str != '\0')
	{
		while (ft_is_space(str))
			str++;
		if (*str == '\0')
			return (head);
		cur_token = token_list_append(&head);
		str += set_token(cur_token, str, head);
	}
	return (head);
}
