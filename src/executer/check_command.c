/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 13:15:34 by jopeters          #+#    #+#             */
/*   Updated: 2024/01/03 16:23:31 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*check_direct_path(t_ms *ms, char *path)
{
	printf("check_direct_path() path >%s<\n", path);
	if (!access(path, F_OK))
	{
		if (!access(path, X_OK))
			return (path);
		else
		{
			ft_putstr_fd("minishell: ", 3);
			ft_putstr_fd(path, 3);
			ft_putstr_fd(": ", 3);
			ft_putendl_fd(strerror(errno), 3);
			exit_with_code(ms, 126);
		}
	}
	else
	{
		ft_putstr_fd("minishell: ", 3);
		ft_putstr_fd(path, 3);
		ft_putstr_fd(": ", 3);
		ft_putendl_fd(strerror(errno), 3);
		exit_with_code(ms, 127);
	}
	return (NULL);
}

static char	*check_env_paths(t_ms *ms, char *prog_name)
{
	char	*tmp_prog;
	int		i;

	i = 0;
	while (ms->path_arr[i])
	{
		tmp_prog = join_three_string(ms->path_arr[i], "/", prog_name);
		if (!access(tmp_prog, F_OK))
			return (tmp_prog);
		else
		{
			if (tmp_prog)
				free(tmp_prog);
			tmp_prog = NULL;
		}
		i++;
	}
	return (NULL);
}

// check every Path in PATH Array with program name; returns a valid path or NULL
char *check_program_with_path(t_ms *ms, char *input)
{
	if (ft_strchr(input, '/')) // if input contains a '/' it is a direct path
	{
		if (check_direct_path(ms, input))
			return (input);
	}
	return (check_env_paths(ms, input));
}
