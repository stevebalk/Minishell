/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 13:15:34 by jopeters          #+#    #+#             */
/*   Updated: 2024/01/05 16:38:42 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	check_if_its_a_file(t_ms *ms, char *path)
{
	if (!is_regular_file(path))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd("is a directory", STDERR_FILENO);
		exit_with_code(ms, 126);
	}
}

static char	*check_direct_path(t_ms *ms, char *path)
{
	if (!access(path, F_OK))
	{
		check_if_its_a_file(ms, path);
		if (!access(path, X_OK))
			return (path);
		else
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(path, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
			exit_with_code(ms, 126);
		}
	}
	else
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		exit_with_code(ms, 127);
	}
	return (NULL);
}

static char	*check_env_paths(t_ms *ms, char *prog_name)
{
	char	*tmp_prog;
	int		i;

	i = 0;
	while (ms->path_arr && ms->path_arr[i])
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
	if (ft_strlen(input) == 0)
		return (NULL);
	else if (ft_strchr(input, '/')) // if input contains a '/' it is a direct path
	{
		if (check_direct_path(ms, input))
			return (input);
	}
	return (check_env_paths(ms, input));
}
