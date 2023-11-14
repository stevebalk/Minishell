/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:13:27 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/14 14:24:00 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

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
		if (ft_is_space(str))
		{
			str++;
			continue ;
		}
		if (*str == '\0')
			return (head);
		if (head != NULL)
		{
			cur_token->next = create_token(head);
			cur_token = cur_token->next;
		}
		else
		{
			head = create_token(head);
			cur_token = head;
		}
		if (ft_strchr(TOKEN_TYPES, *str))
			str += set_special_token(str, cur_token, head);
		else
			str += set_word_token(str, cur_token, head);
	}
	return (head);
}
