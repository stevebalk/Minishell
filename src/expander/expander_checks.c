/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_checks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:14:53 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/22 14:38:48 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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