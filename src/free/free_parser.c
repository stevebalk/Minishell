/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:04:10 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/05 14:10:38 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Free one redir node and NULLs it */
void	free_redir_node(t_redir **node)
{
	if (node && *node)
	{
		if ((*node)->target)
			free((*node)->target);
		free(*node);
	}
	*node = NULL;
}

/* Free redir list and NULLs it */
void	free_redir_list(t_redir **list)
{
	t_redir	*cur;
	t_redir	*next;

	if (list == NULL || *list == NULL)
		return ;
	cur = *list;
	while (cur != NULL)
	{
		next = cur->next;
		free_redir_node(&cur);
		cur = next;
	}
	*list = NULL;
}

/* Free one cmd list and NULLs it */
void	free_cmd_list(t_cmd **list)
{
	t_cmd	*cur;
	t_cmd	*next;

	if (list == NULL || *list == NULL)
		return ;
	cur = *list;
	while (cur != NULL)
	{
		next = cur->next;
		if (cur->argv != NULL)
			ft_free_array((void **)cur->argv);
		if (cur->redirs != NULL)
			free_redir_list(&(cur->redirs));
		free(cur);
		cur = next;
	}
	*list = NULL;
}
