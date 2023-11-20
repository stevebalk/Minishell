/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:07:23 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/20 17:29:41 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_word_len(t_token *tk, char **envp)
{
	size_t	ret;


	while (tk->join == 1)
	{
		if ()
	}
}

void	expand_word(t_token *tk, char **envp)
{
	size_t	len;
	char	*str;
	// len = get_word_len(tk);
	str = tk->content;
	while (*str )
	while (tk->join == 1)

	if ()
}

t_token *expander(t_token *tk, char **envp)
{
	t_token	*cur;

	cur = tk;
	while(cur != NULL)
	{
		if (tk->type == TOKEN_WORD)
			expand_word(tk, envp);
		cur = cur->next;
	}
}