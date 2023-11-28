/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 20:19:56 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/28 17:44:24 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_cmd	*create_cmd_node(t_token *lx)
// {
// 	t_cmd	*ret;

// 	ret = ft_calloc(1, sizeof(t_cmd));
// 	if (ret == NULL)
// 		lx_error(lx, "Malloc failed", 1, 1);
// 	return (ret);
// }


// t_cmd	*get_last_cmd_node(t_cmd *cmds)
// {
// 	t_cmd	*cur;

// 	cur = cmds;
// 	if (cur == NULL)
// 		return (NULL);
// 	while (cur->next != NULL)
// 		cur = cur->next;
// 	return (cur);
// }

// void	match_token(t_token **lx, t_cmd *cmds)
// {
// 	if ((*lx)->type == TOKEN_INFILE || (*lx)->type == TOKEN_HERE_DOC ||
// 		(*lx)->type == TOKEN_REDIRECT || (*lx)->type == TOKEN_REDIRECT_APPEND)
// 	{
// 		cmds->redirs.type = (*lx)->type;
// 		cmds->redirs.param = (*lx)->next->content
// 	}
// }

// void	fill_cmds(t_token **lx, t_cmd *cmds)
// {
// 	t_cmd	*cur;

// 	cur = get_last_cmd_node(cmds);
// 	if (cur == NULL)
// 		cur = create_cmd_node();
// 	while ((*lx)->type != NULL && (*lx)->type != TOKEN_PIPE)
// 	{
// 		match_token(lx, cur);
// 	}

// }

// void	append_cmd_node(t_parse *parse)
// {
// 	t_cmd	*cur;

// 	if (parse && parse->cmd == NULL)
// 	{
// 		parse->cmd = ft_calloc(1, sizeof(t_cmd));
// 		if (parse->cmd == NULL)
// 			parse_error(parse, "Malloc failed", 1, 1);
// 		return;
// 	}
// 	cur = parse->cmd;
// 	while (cur->next != NULL)
// 		cur = cur->next;
// 	cur->next = calloc(1, sizeof(t_cmd));
// 	if (cur->next == NULL)
// 			parse_error(parse, "Malloc failed", 1, 1);
// }

// void	parse_token(t_parse *parse)
// {
// 	if (parse->tk->type == TOKEN_WORD)
		
// }

// t_cmd	parser(t_token *lx)
// {
// 	t_parse	parse;

// 	parse.tk = lx;
// 	parse.cmd = NULL;
// 	while (parse.tk != NULL)
// 	{
// 		append_cmd_node(&parse);
// 		while(parse.tk != NULL && parse.tk->type != TOKEN_PIPE)
// 		{
// 			parse_token(lx, cur);
			
// 		}
// 		// cur = ft_calloc(1, sizeof(t_cmd));
// 		// if (cur == NULL)
// 		// 	lx_error(lx, "Malloc failed", 1, 1);
// 		// if (cmds == NULL)
// 		// 	cmds = cur;
// 		fill_cmds(&lx, cmds);
// 	}
// }

void	fill_cmd_node(t_ms *ms, t_cmd *cmd_node)
{
	t_token	*next;

	next = ms->tk->next;
	if (ms->tk->type == TOKEN_PIPE)
	{
		free_token(ms->tk);
		ms->tk = next;
	}
	
}

void	parse(t_ms *ms)
{
	t_token	*next;
	t_cmd	*cur;

	while (ms->tk)
	{
		append_cmd_node(ms);
		fill_cmd_node(ms, cur);
		next = ms->tk->next;
		
		free_token(ms->tk);
		ms->tk = next;
	}
}