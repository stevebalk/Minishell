/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:38:01 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/27 14:18:25 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// DELETE LATER ///
/* TEST FUNCTION */
char	*get_env_variable_value(char *var_name)
{
	if (var_name)
	{
		return(ft_strdup("_*VAR*_"));
	}
	return (NULL);
}

/* Checks if variable is "$?" alias last exit code */
size_t	is_exit_code_variable(const char *str)
{
	if (ft_strncmp(str, "$?", 2) == 0)
		return (1);
	return (0);
}

// static void expand_to_prev_exit_code(char **str, t_expand *chunk, t_ms *ms)
static void expand_to_prev_exit_code(char **str, t_ms *ms)
{
	size_t	exit_code_len;

	exit_code_len = ft_strlen(ms->last_exit_code);
	*str += 2;
	append_and_fill_chunk_with_str(ms, ms->last_exit_code, exit_code_len);
	// chunk->str = ft_strdup(ms->last_exit_code);
	// check_if_malloc_failed((void *)chunk->str, ms);
}

int	is_numerical_variable(char *str)
{
	if (str[0] == '$' && ft_isdigit(str[1]))
		return (1);
	return (0);
}

int	is_metachar_variable(char *str)
{
	if (str[0] == '$' && !ft_isalpha(str[1]) && str[1] != '_')
		return (1);
	return (0);
}

// void	copy_until_blocker(char **str, t_expand *chunk, t_ms *ms)
void	copy_until_blocker(char **str, t_ms *ms)
{
	char		*str_start;

	str_start = *str;
	while (!ft_is_space(*str) && !is_quote(*str) && **str != '\0')
		(*str)++;
	append_and_fill_chunk_with_str(ms, str_start, *str- str_start);
	// chunk->str = malloc((*str - str_start + 1) * sizeof(char));
	// check_if_malloc_failed((void *)chunk->str, ms);
	// ft_strlcpy(chunk->str, str_start, *str - str_start + 1);
}

void	copy_env_variable(char **str, t_ms *ms, char *quote)
{
	char		*env_var_name;
	char		*env_value;
	char		*str_start;
	// t_expand	*chunk;

	// chunk = append_chunk(ms);
	str_start = *str;
	(*str)++;
	while ((ft_isalnum(**str) || **str == '_') && **str != '\0')
		(*str)++;
	env_var_name = malloc((*str - str_start + 1) * sizeof(char));
	check_if_malloc_failed((void *)env_var_name, ms);
	ft_strlcpy(env_var_name, str_start, *str - str_start + 1);
	env_value = get_env_variable_value(env_var_name); /// NEEEEEEED FUNCTION
	free(env_var_name);
	if (*quote == '\"' && env_value == NULL)
		append_and_fill_chunk_with_str(ms, "", 0);
		// chunk->str = ft_strdup("");
	if (env_value == NULL)
		return ;
	append_and_fill_chunk_with_str(ms, env_value, ft_strlen(env_value));
	free(env_value);
	// ft_strlcpy(chunk->str, env_value, ft_strlen(env_value) + 1);
}

void	create_empty_string_chunk(t_ms *ms)
{
	t_expand	*chunk;

	chunk = append_chunk(ms);
	chunk->str = ft_strdup("");
	check_if_malloc_failed((void *) chunk->str, ms);
}

void	expand_numerical_variable(char **str, t_ms *ms, char *prev_quote)
{
	(*str) += 2;
	if (is_double_quote(prev_quote))
		return (create_empty_string_chunk(ms));
	return ;
}

void	expand_env_varible(char **str, t_ms *ms, char *prev_quote)
{
	if (is_numerical_variable(*str)) // "$2"
	{
		expand_numerical_variable(str, ms, prev_quote);
		return ;
	}
	if (is_exit_code_variable(*str)) // "$?"
	{
		expand_to_prev_exit_code(str, ms);
		return ;
	}
	if (is_metachar_variable(*str)) // "$///" or "$."
	{
		copy_until_blocker(str, ms);
		return ;
	}
	else	// $adas or $dadas...
	{
		copy_env_variable(str, ms, prev_quote);
	}
}
