/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:29:24 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/18 16:28:33 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_quotes(const char *str)
{
	while (*str)
	{
		if (is_quote(str))
			return (1);
		str++;
	}
	return (0);
}

size_t	get_new_delim_len(char *str)
{
	size_t	len;
	size_t	i;

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
		return ;
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
	char	*new_delimiter;
	size_t	len;
	size_t	src_pos;
	size_t	dst_pos;

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

void	concatinate_line_input_to_str(char **dst, char *src)
{
	char	*temp;

	temp = *dst;
	*dst = malloc(ft_strlen(temp) + ft_strlen(src) + 2);
	if (temp != NULL)
	{
		ft_strlcpy(*dst, temp, ft_strlen(temp) + 1);
		ft_strlcat(*dst, src,
					ft_strlen(*dst) + ft_strlen(src) + 1);
		ft_strlcat(*dst, "\n", ft_strlen(*dst) + 2);
		free(temp);
	}
	else
	{
		ft_strlcpy(*dst, src, ft_strlen(src) + 1);
		ft_strlcat(*dst, "\n", ft_strlen(*dst) + 2);
	}
}

char *read_multiline_input(const char *prompt, char *delimiter)
{
	char	*line;
	char	*multiline_input;

	multiline_input = NULL;
	line = readline(prompt);
	while (ft_strncmp(line, delimiter, ft_strlen(delimiter)) != 0 ||
			ft_strncmp(line, delimiter, ft_strlen(line)) != 0)
	{
		concatinate_line_input_to_str(&multiline_input, line);
		free(line);
		line = readline(prompt);
	}
	if (line)
		free(line);
	return (multiline_input);
}

size_t	get_env_var_name_len(char *str)
{
	char	*cur;

	cur = str;
	cur++;
	while (*cur && (ft_isalnum(*cur) || *cur == '_'))
		cur++;
	return (cur - str);
}

void	write_env_var(char **str, t_ms *ms)
{
	char	*env_variable;
	char	*var_name;
	size_t	var_name_len;

	var_name_len = get_env_var_name_len(*str) - 1;
	var_name = malloc((var_name_len + 1) * sizeof(char));
	check_if_malloc_failed((void *) var_name, ms);
	ft_strlcpy(var_name, (*str) + 1, var_name_len + 1);
	(*str) += var_name_len;
	env_variable = get_val_of_var(&(ms->env_llst), var_name);
	free(var_name);
	if (env_variable == NULL)
		return ;
	write(STDOUT_FILENO, env_variable, ft_strlen(env_variable));
	if (env_variable)
		free(env_variable);
}

void	print_expanded_heredoc_string(char *str, t_ms *ms)
{
	char	*exit_code;

	while (*str)
	{
		if (is_numerical_variable(str))
			str++;
		else if(is_exit_code_variable(str))
		{
			exit_code = ft_itoa(ms->last_exit_code);
			write(STDOUT_FILENO, exit_code, ft_strlen(exit_code));
			(*str)++;
			free(exit_code);
		}
		else if (*str == '$' && !is_metachar_variable(str))
			write_env_var(&str, ms);
		else
			write(STDOUT_FILENO, str, 1);
		str++;
	}
}

char	*heredoc(char *delimiter, t_ms *ms)
{
	int		should_expand_env_var;
	char	*expanded_delim;
	char	*heredoc_string;
	
	expanded_delim = NULL;

	should_expand_env_var = !has_quotes(delimiter);
	if (!should_expand_env_var)
	{
		expanded_delim = expand_delimiter(delimiter);
		heredoc_string = read_multiline_input("> ", expanded_delim);
	}
	else
		heredoc_string = read_multiline_input("> ", delimiter);
	if (should_expand_env_var)
		print_expanded_heredoc_string(heredoc_string, ms);
	else
		write(STDOUT_FILENO, heredoc_string, ft_strlen(heredoc_string));
	if (expanded_delim)
		free(expanded_delim);
	return (heredoc_string);
}
