/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_checks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:14:53 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/23 10:46:54 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Returns TRUE if ' or " */
int	is_quote(char *str)
{
	if (ft_strchr(QUOTE, *str) == NULL)
		return (0);
	return (1);
}

/* Returns TRUE if ' */
int	is_single_quote(char *str)
{
	if (*str == '\'')
		return (1);
	return (0);
}

/* Returns TRUE if " */
int	is_double_quote(char *str)
{
	if (*str == '\"')
		return (1);
	return (0);
}

/* Returns TRUE if "$" */
int	is_variable(char *str)
{
	if (*str == '$')
		return (1);
	return (0);
}

/* Checks if any quote has a closing quote */
void	check_valid_quote_count(t_token *token, t_ms *ms)
{
	char	*str;
	char	quote;

	quote = 0;
	str = token->content;
	while (*str != '\0')
	{
		if ((*str == '\'' || *str == '\"') && quote == 0)
			quote = *str;
		else if (*str == quote)
			quote = 0;
	}
	if (quote != 0)
		ms_error(ms, "Wrong number of quotes", 1, 0);
}