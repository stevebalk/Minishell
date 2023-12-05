/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_list_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:59:56 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/05 14:03:01 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Appends a redir node to the given cmd node */
t_redir	*append_redir_node(t_ms *ms, t_cmd *cmd)
{
	t_redir	*new_node;
	t_redir	*cur;

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
	return (new_node);
}

/* Checks the given redir list and deletes every NOT 
heredoc node, return new list that only contains heredoc nodes
or NULL if it was empty */
t_redir	*create_heredoc_only_redir(t_redir *list)
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
			free_redir_node(&list);
		list = old_next;
	}
	return (new_list);
}
