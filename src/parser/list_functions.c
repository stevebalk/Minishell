/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:47:50 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/01 16:49:02 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*append_redir_node(t_ms *ms, t_cmd *cmd)
{
	t_redir	*new_node;
	t_redir *cur;
	
	new_node = ft_calloc(1, sizeof(t_redir));
	check_if_malloc_failed((void *) new_node, ms);
	if (cmd->redirs == NULL)
	{
		cmd->redirs = new_node;
		return (new_node);
	}
	cur = cmd->redirs;
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = new_node;
	return(new_node);
}

/* Create a cmd node and initalize it */
t_cmd	*create_cmd_node(t_ms *ms)
{
	t_cmd	*node;

	node = ft_calloc(1,  sizeof(t_cmd));
	check_if_malloc_failed((void *)node, ms);
	// node->next = NULL;
	// node->argv = NULL;
	// node->redirs = NULL;
	return (node);
}

/* Appends to the ms.cmd linked list or creates the
first node if there isn't one */
t_cmd	*append_cmd_node(t_ms *ms)
{
	t_cmd	*cur;

	if (ms->cmd == NULL)
	{
		ms->cmd = create_cmd_node(ms);
		return (ms->cmd);
	}
	cur = ms->cmd;
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = create_cmd_node(ms);
	return (cur->next);
}

static t_redir	*create_heredoc_only_redir(t_redir *list)
{
	t_redir	*new_list;
	t_redir	*last_new_node;
	t_redir	*old_next;

	new_list = NULL;
	while (list)
	{
		old_next = list->next;
		if (list->type == TOKEN_HERE_DOC)
		{
			if (new_list == NULL)
				new_list = list;
			else
				last_new_node->next = list;
			last_new_node = list;
			last_new_node->next = NULL;
		}
		else
			free_redir_node(list);
		list = old_next;
	}
	return (new_list);
}

t_cmd	*free_cmd_list_exept_here_doc(t_cmd **cmd)
{
	t_cmd	*cmd_next;
	t_cmd	*new_list;
	t_cmd	*last_new_node;

	if (!cmd)
		return (NULL);
	new_list = NULL;
	while (*cmd)
	{
		cmd_next = (*cmd)->next;
		ft_free_array((void **) (*cmd)->argv);
		(*cmd)->argv = NULL;
		(*cmd)->redirs = create_heredoc_only_redir((*cmd)->redirs);
		if ((*cmd)->redirs != NULL)
		{
			if (new_list == NULL)
				new_list = *cmd;
			else
				last_new_node->next = *cmd;
			last_new_node = *cmd;
			last_new_node->next = NULL;
		}
		else
			free(*cmd);
		*cmd = cmd_next;
	}
	return (new_list);
}
