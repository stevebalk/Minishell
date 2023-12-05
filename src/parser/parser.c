/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 20:19:56 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/05 13:57:28 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Appends one cmd argv to the array and returns 
the last char pointer. If no argv exists also creates
one. List ends with NULL */
char	**append_cmd_argv(t_ms *ms, t_cmd *cmd_node)
{
	size_t	i;
	size_t	size;
	char	**temp;

	i = 0;
	size = 0;
	while (cmd_node->argv && cmd_node->argv[size] != NULL)
		size++;
	temp = ft_calloc(size + 2, sizeof(char *));
	check_if_malloc_failed((void *) temp, ms);
	while (i < size)
	{
		temp[i] = cmd_node->argv[i];
		i++;
	}
	free(cmd_node->argv);
	cmd_node->argv = temp;
	return (temp + size);
}

/* Appends cmd argv with reused char pointer from
the token, so it frees only the token without the 
content */
void	parse_word_token(t_ms *ms, t_cmd *cmd_node)
{
	char	**dst;
	t_token	*next;

	next = ms->tk->next;
	dst = append_cmd_argv(ms, cmd_node);
	*dst = ms->tk->content;
	free_token_but_not_content(&(ms->tk));
	ms->tk = next;
}

/* Parse special token, return -1 if next token is not a TOKEN_WORD */
int	parse_special_token(t_ms *ms, t_cmd *cmd_node)
{
	t_redir	*cur;
	t_token	*new_target;

	if (ms->tk->next == NULL)
		return (unexpected_token(ms, "newline", 1));
	else if (ms->tk->next->type != TOKEN_WORD)
		return (unexpected_token(ms, ms->tk->next->content, 1));
	cur = append_redir_node(ms, cmd_node);
	cur->type = ms->tk->type;
	cur->target = ms->tk->next->content;
	new_target = ms->tk->next->next;
	free_token_but_not_content(&(ms->tk->next));
	free_token(&(ms->tk));
	ms->tk = new_target;
	return (0);
}

/* Fills a cmd node, return -1 if parse special token failed */
int	fill_cmd_node(t_ms *ms, t_cmd *cmd_node)
{
	t_token	*next;

	while (ms->tk != NULL && ms->tk->type != TOKEN_PIPE)
	{
		if (ms->tk->type == TOKEN_WORD)
			parse_word_token(ms, cmd_node);
		else
			if (parse_special_token(ms, cmd_node) == -1)
				return (-1);
	}
	if (ms->tk && ms->tk->type == TOKEN_PIPE)
	{
		if (ms->tk->next && ms->tk->next->type == TOKEN_PIPE)
			return (unexpected_token(ms, ms->tk->next->content, 1));
		else if (ms->tk->next == NULL)
			return (unexpected_token(ms, "newline", 1));
		next = ms->tk->next;
		free_token(&(ms->tk));
		ms->tk = next;
	}
	return (0);
}

/* Parse token list, returns -1 if an error occured */
int	parse(t_ms *ms)
{
	t_cmd	*cur;

	if (ms->tk && ms->tk->type == TOKEN_PIPE)
		return (unexpected_token(ms, "|", 1));
	while (ms->tk)
	{
		cur = append_cmd_node(ms);
		if (fill_cmd_node(ms, cur) == -1)
			break ;
	}
	return (0);
}
