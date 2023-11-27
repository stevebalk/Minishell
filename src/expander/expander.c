/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:07:23 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/27 14:55:23 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Create and fill chunk with given str */
void	append_and_fill_chunk_with_str(t_ms *ms, const char *src, size_t len)
{
	t_expand	*chunk;

	chunk = append_chunk(ms);
	chunk->str = malloc((len + 1) * sizeof(char));
	check_if_malloc_failed((void *) chunk->str, ms);
	ft_strlcpy(chunk->str, src, len + 1);
}

/* Expands text that is not inside quotes */
void	expand_no_quotes(char **str, t_ms *ms, char *quote)
{
	size_t		len;
	char		*str_start;

	len = 0;
	str_start = *str;
	if (is_env_variable(*str))
	{
		expand_env_varible(str, ms, quote);
		return ;
	}
	while (!is_quote(*str) && !is_env_variable(*str) && **str != '\0')
	{
		len++;
		(*str)++;
	}
	append_and_fill_chunk_with_str(ms, str_start, len);
}

/* Expands text that is inside single quotes */
void	expand_single_quote_content(char **str, t_ms *ms)
{
	size_t		len;
	char		*str_start;
	// t_expand	*chunk;

	// append_chunk(ms);
	len = 0;
	(*str)++;
	str_start = *str;
	while(!is_single_quote(*str))
	{
		(*str)++;
		len++;
	}
	// if (len == 0)
	// 	return (chunk->str = ft_strdup(""), NULL);
	append_and_fill_chunk_with_str(ms, str_start, len);
	(*str)++;
}

void	expand_double_quote_content(char **str, t_ms *ms, char *prev_quote)
{
	size_t		len;
	char		*str_start;
	len = 0;
	if (is_env_variable(*str))
	{
		expand_env_varible(str, ms, prev_quote);
		return ;
	}
	if (!is_double_quote(prev_quote))
	{
		*prev_quote = '\"';
		(*str)++;
	}
	str_start = *str;
	while (!is_double_quote(*str))
	{
		if (is_env_variable(*str))
		{
			break;
			// expand_env_varible(str, ms, prev_quote);
			// return ;
		}
		len++;
		(*str)++;
	}
	append_and_fill_chunk_with_str(ms, str_start, len);
	if (is_double_quote(*str))
	{
		*prev_quote = 0;
		(*str)++;
	}
}

char	*join_chunks_to_final_word(t_ms *ms)
{
	t_expand	*cur;
	t_expand	*next;
	char		*final_string;
	size_t		final_str_len;
	int			legit_str;

	legit_str = 0;
	final_str_len = 0;
	cur = ms->exp;
	while (cur)
	{
		if (cur->str != NULL)
			legit_str = 1;
		final_str_len += ft_strlen(cur->str);
		cur = cur->next;
	}
	if (legit_str && final_str_len == 0)
		return (ft_strdup(""));
	else if (legit_str == 0 && final_str_len == 0)
	{
		free(ms->exp);
		return (NULL);
	}
	cur = ms->exp;
	final_string = ft_calloc(final_str_len + 1, sizeof(char));
	check_if_malloc_failed((void *)final_string, ms);
	while (cur)
	{
		ft_strlcat(final_string, cur->str, ft_strlen(cur->str)
					 + ft_strlen(final_string) + 1);
		next = cur->next;
		if (cur->str)
			free(cur->str);
		free(cur);
		cur = next;
	}
	ms->exp = NULL;
	return (final_string);
}

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
	// t_expand	*DEBUG = ms->exp;
	// printf("New: ");
	// while (DEBUG != NULL)
	// {
	// 	if (DEBUG->str)
	// 		printf("%s", DEBUG->str);
	// 	DEBUG = DEBUG->next;
	// }
	// printf("\n");
	// free_exp(ms->exp);
	ms->exp = NULL;
}

/* Checks all lexer tokens for TOKEN_WORD, expands env variables
(if valid) and remove quotes */
void	expander(t_ms *ms)
{
	t_token	*cur;
	// char	*old_string;

	cur = ms->tk;
	while (cur != NULL)
	{
		if (cur->type == TOKEN_WORD)
		{
			check_if_valid_quote_count(cur, ms);
			// old_string = cur->content;
			expand_word_token(cur, ms);
			// printf("Old: %s\n", old_string);
			// free(old_string);
		}
		cur = cur->next;
	}
}
