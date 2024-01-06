/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:29:24 by sbalk             #+#    #+#             */
/*   Updated: 2024/01/06 12:01:59 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *read_multiline_input(const char *prompt, char *delimiter, int *is_valid)
{
	char *line;
	char *multiline_input;

	tty_set_flag(TTY_HEREDOC, 1);
	multiline_input = NULL;
	line = readline(prompt);
	if (!tty_get_flag(TTY_HEREDOC))
	{
		*is_valid = 0;
		return (NULL);
	}
	while (line && (ft_strncmp(line, delimiter, ft_strlen(delimiter)) != 0 ||
					ft_strncmp(line, delimiter, ft_strlen(line)) != 0))
	{
		concatinate_line_input_to_str(&multiline_input, line);
		free(line);
		line = readline(prompt);
		if (!tty_get_flag(TTY_HEREDOC))
		{
			free(multiline_input);
			*is_valid = 0;
			return (NULL);
		}
	}
	if (line)
		free(line);
	tty_set_flag(TTY_HEREDOC, 0);
	return (multiline_input);
}

char *heredoc(char *delimiter, t_ms *ms, int *is_valid)
{
	int should_expand_env_var;
	char *expanded_delim;
	char *heredoc_string;

	expanded_delim = NULL;

	should_expand_env_var = !has_quotes(delimiter);
	if (!should_expand_env_var)
	{
		expanded_delim = expand_delimiter(delimiter);
		heredoc_string = read_multiline_input("> ", expanded_delim, is_valid);
	}
	else
		heredoc_string = read_multiline_input("> ", delimiter, is_valid);
	if (should_expand_env_var)
		heredoc_string = expand_heredoc_string(heredoc_string, ms);
	if (expanded_delim)
		free(expanded_delim);
	if (heredoc_string == NULL)
		heredoc_string = ft_strdup("");
	return (heredoc_string);
}
