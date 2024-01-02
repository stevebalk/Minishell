/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_io.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:23:24 by sbalk             #+#    #+#             */
/*   Updated: 2024/01/02 14:46:53 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*get_heredoc_string(t_ms *ms, t_redir *redir)
// {
// 	t_redir *cur;
// 	char	*ret;

// 	if (redir == NULL)
// 		return (NULL);
// 	ret = NULL;
// 	cur = redir;
// 	while (cur)
// 	{
// 		if (cur->type == TOKEN_HERE_DOC)
// 		{
// 			if (ret)
// 				free(ret);
// 			ret = heredoc(cur->target, ms);
// 		}
// 		cur = cur->next;
// 	}
// 	return (ret);
// }

// static void	fill_cmd_io_node(t_ms *ms, t_redir *redir, t_cmd_io *io)
// {
// 	t_redir	*cur;
// 	char	*heredoc_string;

// 	if (redir == NULL)
// 		return ;
// 	heredoc_string = get_heredoc_string(ms, redir);
// 	cur = redir;
// 	while (cur)
// 	{
// 		io->is_valid = redir_to_io(cur, io, heredoc_string);
// 		if (io->is_valid)
// 			cur = cur->next;
// 		else
// 		{
// 			// ft_free_array((void**)io->command_arr);
// 			io->command_arr = NULL;
// 			break;
// 		}
// 	}
// 	if (io->intype != TOKEN_HERE_DOC)
// 		free(heredoc_string);
// }

// void	create_cmd_io_list(t_ms *ms)
// {
// 	t_cmd		*cmd_cur;
// 	t_cmd_io	*cmd_io_cur;

// 	cmd_cur = ms->cmd;
// 	while (cmd_cur)
// 	{
// 		cmd_io_cur = cmd_io_append_node(ms);
// 		cmd_io_cur->command_arr = cmd_cur->argv;
// 		fill_cmd_io_node(ms, cmd_cur->redirs, cmd_io_cur);
// 		cmd_cur = cmd_cur->next;
// 	}
// }
