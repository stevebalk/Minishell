/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:53:38 by sbalk             #+#    #+#             */
/*   Updated: 2024/01/06 12:03:03 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_new_delim_len(char *str)
{
	size_t len;
	size_t i;

	len = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '$')
			{
				len += 2;
				i++;
			}
			else if (!is_quote(str + i + 1))
				len++;
		}
		else if (!is_quote(str + i))
			len++;
		i++;
	}
	return (len);
}

void	expand_dollar_sign(char *dst, char *src,
						size_t *src_pos, size_t *dst_pos)
{
	if (is_quote(&(src[*src_pos + 1])))
		return;
	else if (src[*src_pos + 1] == '$')
	{
		dst[*dst_pos] = src[*src_pos];
		dst[*dst_pos + 1] = src[*src_pos + 1];
		(*src_pos)++;
		(*dst_pos) += 2;
	}
	else
	{
		dst[*dst_pos] = src[*src_pos];
		(*dst_pos)++;
	}
}

char	*expand_delimiter(char *str)
{
	char *new_delimiter;
	size_t len;
	size_t src_pos;
	size_t dst_pos;

	len = get_new_delim_len(str);
	new_delimiter = ft_calloc(len + 1, sizeof(char));
	src_pos = 0;
	dst_pos = 0;
	while (str[src_pos] != '\0')
	{
		if (str[src_pos] == '$')
			expand_dollar_sign(new_delimiter, str, &src_pos, &dst_pos);
		else if (!is_quote(str + src_pos))
			new_delimiter[dst_pos++] = str[src_pos];
		src_pos++;
	}
	return (new_delimiter);
}

static void	append_env_var(char **dst_str, char **str, t_ms *ms)
{
	char *env_variable;
	char *var_name;
	size_t var_name_len;

	var_name_len = get_env_var_name_len(*str);
	var_name = malloc((var_name_len) * sizeof(char));
	check_if_malloc_failed((void *)var_name, ms);
	ft_strlcpy(var_name, (*str) + 1, var_name_len);
	(*str) += var_name_len - 1;
	env_variable = get_val_of_var(&(ms->env_llst), var_name);
	free(var_name);
	if (env_variable == NULL)
		return;
	append_string(ms, dst_str, env_variable, ft_strlen(env_variable));
	if (env_variable)
		free(env_variable);
}

char	*expand_heredoc_string(char *str, t_ms *ms)
{
	char *exit_code;
	char *ret_string;
	char *str_start;

	if (str == NULL || *str == '\0')
		return (NULL);
	str_start = str;
	ret_string = NULL;
	while (*str)
	{
		if (is_numerical_variable(str))
			str++;
		else if (is_exit_code_variable(str))
		{
			exit_code = ft_itoa(ms->last_exit_code);
			append_string(ms, &ret_string, exit_code, ft_strlen(exit_code));
			(*str)++;
			free(exit_code);
		}
		else if (*str == '$' && !is_metachar_variable(str))
			append_env_var(&ret_string, &str, ms);
		else
			append_string(ms, &ret_string, str, 1);
		str++;
	}
	free(str_start);
	return (ret_string);
}
