/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:07:23 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/21 16:17:55 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Copy and returns a string enclosed with quotes to a new one without.
Also frees the old string */
char	*copy_without_quotes(char *str, t_token *tk_head)
{
	size_t	len;
	char	quote;
	char	*ret;

	len = 0;
	quote = *str;
	str++;
	while (str[len] != quote)
		len++;
	ret = ft_calloc(len + 1, sizeof(char));
	if (ret == NULL)
		lx_error(tk_head, "Malloc failed", 1, 1);
	ft_strlcpy(ret, str, len + 1);
	return (ret);
}

size_t	get_env_varibale_len(char *str, t_ms *ms)
{
	size_t	len;
	size_t	ret;
	t_list	*envp;

	len = 0;
	ret = 0;
	envp = ms->envp;
	str++;
	while (str[len] != '\0' && str[len] != ' ' && ft_isalnum)
		len++;
	while (envp != NULL)
	{
		if (ft_strncmp((char *) envp->content, str, len) == 0)
			if 
	}
}

/* Creates a new string with expanded variables. Frees the old string */
char	*expand_variables(char *str, t_token *tk_head, t_list *envp, t_ms *ms)
{
	size_t	len;
	size_t	pos;
	char	*ret;

	len = 0;
	pos = 0;
	ret = NULL;
	while(str[pos] != '\0')
	{
		if (str[pos] == '$')
		{
			len += get_env_varibale_len(str + pos, envp);
			pos += move_pos_to_end_of_var(str + pos, envp);
		}
		else
			len++;
	}
	ret = create_expanded_string(str, len);
}


void	expand_word_token_content(t_token *tk, t_list *envp, t_ms *ms)
{
	char	*str;

	if (tk->content == '\'')
	{
		str = copy_without_quotes();
		free(tk->content);
		tk->content = str;
	}
	else if (tk->content == '\"')
	{
		str = copy_withtout_quotes();
		str = expand_variables();
		free(tk->content);
		tk->content = str;
	}
	else
	{
		str = expand_variables();
		free(tk->content);
		tk->content = str;
	}
}

t_token *expander(t_token *tk, t_list *envp, t_ms *ms)
{
	t_token	*cur;

	cur = tk;
	while(cur != NULL)
	{
		if (tk->type == TOKEN_WORD)
			expand_word_token_content(tk, envp);
		cur = cur->next;
	}
}