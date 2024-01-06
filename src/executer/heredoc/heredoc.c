/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:29:24 by sbalk             #+#    #+#             */
/*   Updated: 2024/01/06 13:18:11 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	read_next_lines(char **dst, char **src,
				char *delimiter, int *is_valid)
{
	while (*src && (ft_strncmp(*src, delimiter, ft_strlen(delimiter)) != 0
			|| ft_strncmp(*src, delimiter, ft_strlen(*src)) != 0))
	{
		concatinate_line_input_to_str(dst, *src);
		free(*src);
		*src = readline("> ");
		if (!tty_get_flag(TTY_HEREDOC))
		{
			free(dst);
			*is_valid = 0;
			return (0);
		}
	}
	if (*src)
		free(*src);
	return (1);
}

char	*read_multiline_input(char *delimiter, int *is_valid)
{
	char	*line;
	char	*multiline_input;

	tty_set_flag(TTY_HEREDOC, 1);
	multiline_input = NULL;
	line = readline("> ");
	if (!tty_get_flag(TTY_HEREDOC))
	{
		*is_valid = 0;
		return (NULL);
	}
	if (!read_next_lines(&multiline_input, &line, delimiter, is_valid))
		return (NULL);
	tty_set_flag(TTY_HEREDOC, 0);
	return (multiline_input);
}

char	*heredoc(char *delimiter, t_ms *ms, int *is_valid)
{
	int		should_expand_env_var;
	char	*expanded_delim;
	char	*heredoc_string;

	expanded_delim = NULL;
	should_expand_env_var = !has_quotes(delimiter);
	if (!should_expand_env_var)
	{
		expanded_delim = expand_delimiter(delimiter);
		heredoc_string = read_multiline_input(expanded_delim, is_valid);
	}
	else
		heredoc_string = read_multiline_input(delimiter, is_valid);
	if (should_expand_env_var)
		heredoc_string = expand_heredoc_string(heredoc_string, ms);
	if (expanded_delim)
		free(expanded_delim);
	if (heredoc_string == NULL)
		heredoc_string = ft_strdup("");
	return (heredoc_string);
}
