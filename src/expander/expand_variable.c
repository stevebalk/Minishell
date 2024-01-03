/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:38:01 by sbalk             #+#    #+#             */
/*   Updated: 2024/01/03 11:20:59 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// DELETE LATER ///
/* TEST FUNCTION */
char	*get_env_variable_value(char *var_name)
{
	if (var_name)
	{
		return (ft_strdup("_*VAR*_"));
	}
	return (NULL);
}

// static void expand_to_prev_exit_code(char **str, t_expand *chunk, t_ms *ms)
static void	expand_to_prev_exit_code(char **str, t_ms *ms)
{
	char	*exit_code;
	size_t	exit_code_len;

	exit_code = ft_itoa(ms->last_exit_code);
	exit_code_len = ft_strlen(exit_code);
	*str += 2;
	append_and_fill_chunk_with_str(ms, exit_code, exit_code_len);
	free(exit_code);
}

// void	copy_until_blocker(char **str, t_expand *chunk, t_ms *ms)
void	copy_until_blocker(char **str, t_ms *ms)
{
	char		*str_start;

	str_start = *str;
	while (!ft_is_space(*str) && !is_quote(*str) && **str != '\0')
		(*str)++;
	append_and_fill_chunk_with_str(ms, str_start, *str - str_start);
}

/* Searches if an env variable exists and copies it's content
into a new chunk, or if it doesn't exist into a chunk with 
a string of size zero, or doesn't create a chunk at all.
This depends if it inside quotes or not */
void	copy_env_variable(char **str, t_ms *ms, char *quote)
{
	char		*env_var_name;
	char		*env_value;
	char		*str_start;

	str_start = *str;
	(*str)++;
	while ((ft_isalnum(**str) || **str == '_') && **str != '\0')
		(*str)++;
	env_var_name = malloc((*str - str_start + 1) * sizeof(char));
	check_if_malloc_failed((void *)env_var_name, ms);
	ft_strlcpy(env_var_name, str_start + 1, *str - str_start);
	env_value = get_val_of_var(&(ms->env_llst), env_var_name);
	free(env_var_name);
	if (*quote == '\"' && env_value == NULL)
		append_and_fill_chunk_with_str(ms, "", 0);
	if (env_value == NULL)
		return ;
	append_and_fill_chunk_with_str(ms, env_value, ft_strlen(env_value));
	free(env_value);
}

/* Expands env variable like $2 */
void	expand_numerical_variable(char **str, t_ms *ms, char *prev_quote)
{
	(*str) += 2;
	if (is_double_quote(prev_quote))
		return (create_empty_string_chunk(ms));
	return ;
}

/* Checks if and how an env variable should be expanded, and then
expands it */
void	expand_env_varible(char **str, t_ms *ms, char *prev_quote)
{
	if (is_numerical_variable(*str)) // "$2"
		expand_numerical_variable(str, ms, prev_quote);
	else if (is_exit_code_variable(*str)) // "$?"
		expand_to_prev_exit_code(str, ms);
	else if (is_metachar_variable(*str)) // "$///" or "$."
	{
		if (!is_quote((*str) + 1))
		{
			copy_until_blocker(str, ms);
			return ;
		}
		(*str)++;
	}
	else	// $adas or $dadas...
		copy_env_variable(str, ms, prev_quote);
	return ;
}
