/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:14:53 by sbalk             #+#    #+#             */
/*   Updated: 2024/01/03 18:05:34 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Returns TRUE if ' or " */
size_t	is_quote(const char *str)
{
	if (ft_strchr(QUOTE, *str) == NULL)
		return (0);
	return (1);
}

/* Returns TRUE if ' */
size_t	is_single_quote(const char *str)
{
	if (*str == '\'')
		return (1);
	return (0);
}

/* Returns TRUE if " */
size_t	is_double_quote(const char *str)
{
	if (*str == '\"')
		return (1);
	return (0);
}

/* Returns TRUE if "$" */
size_t	is_env_variable(const char *str)
{
	if (*str == '$')
		return (1);
	return (0);
}

/* Checks if any quote has a closing quote */
// int	is_valid_quote_count(t_token *token)
// {
// 	char	*str;
// 	char	quote;

// 	quote = 0;
// 	str = token->content;
// 	while (*str != '\0')
// 	{
// 		if ((*str == '\'' || *str == '\"') && quote == 0)
// 			quote = *str;
// 		else if (*str == quote)
// 			quote = 0;
// 		str++;
// 	}
// 	if (quote != 0)
// 	{
// 		ft_putstr_fd("unexpected EOF while looking for matching `", 2);
// 		ft_putchar_fd(quote, 2);
// 		ft_putstr_fd("'", 2);
// 		ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
// 		return (0);
// 	}
// 	return (1);
// }

/* Checks if any quote has a closing quote */
int	is_valid_quote_count(char *str)
{
	char	quote;

	quote = 0;
	while (*str != '\0')
	{
		if ((*str == '\'' || *str == '\"') && quote == 0)
			quote = *str;
		else if (*str == quote)
			quote = 0;
		str++;
	}
	if (quote != 0)
	{
		ft_putstr_fd("bash: unexpected EOF while looking for matching `", 2);
		ft_putchar_fd(quote, 2);
		ft_putendl_fd("'", 2);
		ft_putendl_fd("minishell: syntax error: unexpected end of file", 2);
		return (0);
	}
	return (1);
}
