/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:23:07 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/20 14:44:59 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Free linked token list. Starting at given node */
void	free_lx(t_token *token)
{
	t_token	*cur;
	t_token	*next;

	cur = token;
	while (cur != NULL)
	{
		next = cur->next;
		if (cur->content != NULL)
			free(cur->content);
		free(cur);
		cur = next;
	}
}

void	free_redir(t_redir *redir)
{
	t_redir	*cur;
	t_redir	*next;

	cur = redir;
	while (cur != NULL)
	{
		next = cur->next;
		if (cur->param != NULL)
			free(cur->param);
		free(cur);
		cur = next;
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*cur;
	t_cmd	*next;

	cur = cmd;
	while (cur != NULL)
	{
		next = cur->next;
		if (cur->argv != NULL)
			ft_free_array((void**)cur->argv);
		if (cur->redirs != NULL)
			free_redir(cur->redirs);
		free(cur);
		cur = next;
	}
}
