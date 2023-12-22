/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:59:59 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/22 12:23:01 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Create a cmd node and initalize it with 0 */
t_cmd	*create_cmd_node(t_ms *ms)
{
	t_cmd	*node;

	node = ft_calloc(1, sizeof(t_cmd));
	check_if_malloc_failed((void *)node, ms);
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

/* Appends a new node to the given list and also saves the tail node
to the given pointer */
static void	append_new_cmd_node(t_cmd **new_list, t_cmd **tail, t_cmd *new_node)
{
	if (*new_list == NULL)
		*new_list = new_node;
	else
		(*tail)->next = new_node;
	*tail = new_node;
	(*tail)->next = NULL;
}

/* Free all content and cmd nodes, except heredoc redirections
and nodes containing them */
void	free_cmd_list_exept_here_doc(t_cmd **cmd)
{
	t_cmd	*cmd_next;
	t_cmd	*new_list;
	t_cmd	*new_list_tail;

	if (!cmd || !*cmd)
		return ;
	new_list = NULL;
	while (*cmd)
	{
		cmd_next = (*cmd)->next;
		ft_free_array((void **)(*cmd)->argv);
		(*cmd)->argv = NULL;
		(*cmd)->redirs = create_heredoc_only_redir((*cmd)->redirs);
		if ((*cmd)->redirs)
			append_new_cmd_node(&new_list, &new_list_tail, *cmd);
		else
			free(*cmd);
		*cmd = cmd_next;
	}
	*cmd = new_list;
}

t_cmd	*free_cmd_head(t_cmd **list)
{
	t_cmd	*cur;
	t_cmd	*next;

	if (list == NULL || *list == NULL)
		return (NULL);
	cur = *list;
	next = (*list)->next;
	free_redir_list(&(cur)->redirs);
	ft_free_array((void **)cur->argv);
	free(cur);
	*list = next;
	return (*list);
}
