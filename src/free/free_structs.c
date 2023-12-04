/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:23:07 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/04 15:46:51 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_token *token)
{
	if (token)
	{
		if (token->content)
			free(token->content);
		if (token->next)
			token->next->prev = NULL;
		free(token);
	}
}

/* Free linked token list. Starting at given node */
void	free_lx(t_token *token)
{
	t_token	*cur;
	t_token	*next;

	if (token == NULL)
		return ;
	cur = token;
	while (cur != NULL)
	{
		next = cur->next;
		free_token(cur);
		cur = next;
	}
}

void	free_redir(t_redir *redir)
{
	t_redir	*cur;
	t_redir	*next;

	if (redir == NULL)
		return ;
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

	if (cmd == NULL)
		return ;
	cur = cmd;
	while (cur != NULL)
	{
		next = cur->next;
		if (cur->argv != NULL)
			ft_free_array((void **)cur->argv);
		if (cur->redirs != NULL)
			free_redir(cur->redirs);
		free(cur);
		cur = next;
	}
}

void	free_exp(t_expand *exp)
{
	t_expand	*next;

	if (exp == NULL)
		return ;
	while (exp != NULL)
	{
		next = exp->next;
		if (exp->str)
			free(exp->str);
		free(exp);
		exp = next;
	}
}

void	free_ms(t_ms *ms)
{
	if (!ms)
		return ;
		
	// free_lx(ms->tk);
	// free_exp(ms->exp);
	// free_cmd(ms->cmd);
	// if (ms->last_exit_code)
	// 	free(ms->last_exit_code);
	//ft_lstclear(&(ms->envp), ft_lstdelone);

	// if (ms->path_arr)
	// 	ft_free_array((void **)ms->path_arr);
	if (ms->home_dir)
		free(ms->home_dir);
	

	lst_dealloc(&ms->hist_llst, 1);
	lst_dealloc(&ms->env_llst, 1);
	lst_dealloc(&ms->env_llst_sorted, 1);
	
	// todo free
	// 
	// 
}

