/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word_chunks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:56:25 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/28 15:29:09 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	len = 0;
	(*str)++;
	str_start = *str;
	while (!is_single_quote(*str))
	{
		(*str)++;
		len++;
	}
	append_and_fill_chunk_with_str(ms, str_start, len);
	(*str)++;
}

/* Expands text that is inside double quotes */
void	expand_double_quote_content(char **str, t_ms *ms, char *prev_quote)
{
	char		*str_start;

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
			break ;
		(*str)++;
	}
	append_and_fill_chunk_with_str(ms, str_start, *str - str_start);
	if (is_double_quote(*str))
	{
		*prev_quote = 0;
		(*str)++;
	}
}
