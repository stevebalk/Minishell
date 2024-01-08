/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:47:21 by sbalk             #+#    #+#             */
/*   Updated: 2024/01/08 14:11:02 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_io(t_ms *ms, t_cmd_io *io)
{
	char	**new_env;
	char	*path_program;

	if (!io->is_valid)
		exit_with_code(ms, 1);
	if (io->command_arr == NULL)
		exit_with_code(ms, 0);
	if (is_builtin_command(io->command_arr[0]))
		exit_with_code(ms, builtin_master(ms, io->command_arr));
	new_env = copy_llst_to_char_arr(&ms->env_llst, ms);
	copy_path_to_ms_struct(ms);
	path_program = check_program_with_path(ms, io->command_arr[0]);
	if (path_program != NULL)
	{
		if (execve(path_program, io->command_arr, new_env) == -1)
		{
			execve_error(io, new_env, path_program);
			exit_with_code(ms, errno);
		}
	}
	command_not_found(io, io->command_arr[0], new_env, path_program);
	exit_with_code(ms, 127);
}

void	run_builtin_in_parent(t_ms *ms, int input_fd)
{
	t_cmd_io	io;

	init_cmd_io(&io);
	set_io_redirections(ms, ms->cmd, &io);
	if (io.is_valid)
	{
		redirect_fds(ms, &io, input_fd, NULL);
		ms->last_exit_code = builtin_master(ms, ms->cmd->argv);
	}
	close_io_fds(&io);
	free_cmd_head(&ms->cmd);
	reset_redirections(ms);
}

int	execute_heredocs(t_ms *ms)
{
	t_cmd	*cur_cmd;
	t_redir	*cur_redir;
	int		is_valid;
	char	*tmp;

	cur_cmd = ms->cmd;
	is_valid = 1;
	while (cur_cmd)
	{
		cur_redir = cur_cmd->redirs;
		while (cur_redir)
		{
			if (cur_redir->type == TOKEN_HERE_DOC)
			{
				tmp = cur_redir->target;
				cur_redir->target = heredoc(cur_redir->target, ms, &is_valid);
				free(tmp);
				if (!is_valid)
					return (0);
			}
			cur_redir = cur_redir->next;
		}
		cur_cmd = cur_cmd->next;
	}
	return (is_valid);
}
