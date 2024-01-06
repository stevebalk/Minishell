/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:07:23 by sbalk             #+#    #+#             */
/*   Updated: 2024/01/06 17:00:54 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ambigous_redirect_error(t_ms *ms, char *file_name)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(file_name, STDERR_FILENO);
	ft_putendl_fd(": ambigous redirect", STDERR_FILENO);
	ms->last_exit_code = 1;
}

/* Expands all legit env variables based on there enclosing quotes
and removes all unecessary quotes */
void	expand_word_token(t_token *tk, t_ms *ms)
{
	char		*str;
	char		prev_quote;
	char		*temp;

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
	temp = join_chunks_to_final_word(ms);
	if (temp == NULL && tk->prev
		&& (tk->prev->type == TOKEN_INFILE || tk->prev->type == TOKEN_REDIRECT
			|| tk->prev->type == TOKEN_REDIRECT_APPEND))
		ambigous_redirect_error(ms, tk->content);
	free(tk->content);
	tk->content = temp;
	ms->exp = NULL;
}

/* Checks all lexer tokens for TOKEN_WORD, expands env variables
(if valid) and remove quotes */
void	expand(t_ms *ms)
{
	t_token	*cur;

	cur = ms->tk;
	while (cur != NULL)
	{
		if (cur->type == TOKEN_WORD)
		{
			if (!cur->prev || (cur->prev && cur->prev->type != TOKEN_HERE_DOC))
				expand_word_token(cur, ms);
		}
		cur = cur->next;
	}
}
