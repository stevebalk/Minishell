/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:07:23 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/28 15:11:10 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Expands all legit env variables based on there enclosing quotes
and removes all unecessary quotes */
void	expand_word_token(t_token *tk, t_ms *ms)
{
	char		*str;
	char		prev_quote;

	str = tk->content;
	prev_quote = 0;
	while (*str != '\0')
	{
		if (!is_quote(str) && !prev_quote)
			expand_no_quotes(&str, ms, &prev_quote);
		else if (is_single_quote(str) && !is_double_quote(&prev_quote))
			expand_single_quote_content(&str, ms);
		else
			expand_double_quote_content(&str, ms, &prev_quote);
	}
	free(tk->content);
	tk->content = join_chunks_to_final_word(ms);
	ms->exp = NULL;
}

/* Checks all lexer tokens for TOKEN_WORD, expands env variables
(if valid) and remove quotes */
void	expander(t_ms *ms)
{
	t_token	*cur;

	cur = ms->tk;
	while (cur != NULL)
	{
		if (cur->type == TOKEN_WORD)
		{
			check_if_valid_quote_count(cur, ms);
			if (!cur->prev || (cur->prev && cur->prev->type != TOKEN_HERE_DOC))
				expand_word_token(cur, ms);
		}
		cur = cur->next;
	}
}
