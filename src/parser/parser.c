/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 20:19:56 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/18 21:11:50 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../include/lexer.h"

t_cmd	*get_last_cmd_node(t_cmd *cmds)
{
	t_cmd	*cur;

	cur = cmds;
	if (cur == NULL)
		return (NULL);
	while (cur->next != NULL)
		cur = cur->next;
	return (cur);
}

void	match_token(t_token **lx, t_cmd *cmds)
{
	if ((*lx)->type == TOKEN_INFILE || (*lx)->type == TOKEN_HERE_DOC ||
		(*lx)->type == TOKEN_REDIRECT || (*lx)->type == TOKEN_REDIRECT_APPEND)
	{
		cmds->redirs.type = (*lx)->type;
		cmds->redirs.param = (*lx)->next->content
	}
}

void	fill_cmds(t_token **lx, t_cmd *cmds)
{
	t_cmd	*cur;

	cur = get_last_cmd_node(cmds);
	if (cur == NULL)
		cur = create_cmd_node();
	while ((*lx)->type != NULL && (*lx)->type != TOKEN_PIPE)
	{
		match_token(lx, cur);
	}

}

t_cmd	parser(t_token *lx)
{
	t_cmd	*cmds;
	t_cmd	*prev;
	t_cmd	*cur;

	cmds = NULL;
	cur = NULL;
	prev = NULL;
	while (lx != NULL)
	{
		// cur = ft_calloc(1, sizeof(t_cmd));
		// if (cur == NULL)
		// 	lx_error(lx, "Malloc failed", 1, 1);
		// if (cmds == NULL)
		// 	cmds = cur;
		fill_cmds(&lx, cmds);

	}
}
