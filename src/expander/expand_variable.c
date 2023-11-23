/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:38:01 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/23 17:18:25 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_exit_code_varible(char *str)
{
	if (*str == '$' && *(str++) == '?')
		return (1);
	return (0);
}

static void expand_to_prev_exit_code(char **str, t_expand *chunk, t_ms *ms)
{
	*str += 2;
	chunk->str = ft_strdup(ms->last_exit_code);
	check_if_malloc_failed((void *)chunk->str, ms);
}

int	is_numerical_variable(char *str)
{
	if (*str == '$' && ft_isdigit(*(str++)))
		return (1);
	return (0);
}

int	is_metachar_variable(char *str)
{
	if (*str == '$' && (ft_isalpha(*(str++)) || *(str++) == '_'))
		return (1);
	return (0);
}

void	copy_until_blocker(char **str, t_expand *chunk, t_ms *ms)
{
	char		*str_start;

	str_start = *str;
	while (!ft_is_space(*str && !is_quote(*str) && **str != '\0'))
		(*str)++;
	chunk->str = malloc((*str - str_start + 1) * sizeof(char));
	check_if_malloc_failed((void *)chunk->str, ms);
	ft_strlcpy(chunk->str, str_start, *str - str_start + 1);
}

char	*copy_variable(char **str, t_expand *chunk, t_ms *ms, char *quote)
{
	char	*env_var_name;
	char	*env_var;
	char		*str_start;

	str_start = *str;
	(*str)++;
	while ((ft_isalnum(*str) || *str == '_') && **str != '\0')
		(*str)++;
	env_var_name = malloc((*str - str_start + 1) * sizeof(char));
	check_if_malloc_failed((void *)env_var_name, ms);
	ft_strlcpy(env_var_name, str_start, *str - str_start + 1);
	env_var = get_env_variable_value(env_var_name); /// NEEEEEEED FUNCTION
	if (quote == '\"' && env_var == NULL)
		return (chunk->str = ft_strdup(""), NULL);
	if (env_var == NULL)
		return ;
	ft_strlcpy(chunk->str, env_var, strlen(env_var) + 1);
}

void	expand_varible(char **str, t_ms *ms, char *quote)
{
	char		*str_start;
	size_t		len;
	t_expand	*chunk;
	size_t		should_expand;

	str_start = *str;
	should_expand = 1;
	chunk = append_chunk(ms);
	if (is_exit_code_variable(*str)) // "$?"
		return (expand_to_prev_exit_code(str, chunk, ms), NULL);
	if (is_numerical_variable(*str)) // "$2"
	{
		(*str) += 2;
		return ;
	}
	if (!is_metachar_variable(*str)) // "$///" or "$."
		return (copy_until_blocker(str, chunk, ms), NULL);
	else	// $adas or $dadas...
		chunk->str = copy_variable(str, chunk, ms, quote);
}
