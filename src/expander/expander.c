/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:07:23 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/25 18:49:29 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Copy and returns a string enclosed with quotes to a new one without.
Also frees the old string */
// char	*copy_without_quotes(char *str, t_token *tk_head)
// {
// 	size_t	len;
// 	char	quote;
// 	char	*ret;

// 	len = 0;
// 	quote = *str;
// 	str++;
// 	while (str[len] != quote)
// 		len++;
// 	ret = ft_calloc(len + 1, sizeof(char));
// 	if (ret == NULL)
// 		lx_error(tk_head, "Malloc failed", 1, 1);
// 	ft_strlcpy(ret, str, len + 1);
// 	return (ret);
// }

// size_t	get_env_varibale_len(char *str, t_ms *ms)
// {
// 	size_t	len;
// 	size_t	ret;
// 	t_list	*envp;

// 	len = 0;
// 	ret = 0;
// 	envp = ms->envp;
// 	str++;
// 	while (str[len] != '\0' && str[len] != ' ' && ft_isalnum)
// 		len++;
// 	while (envp != NULL)
// 	{
// 		if (ft_strncmp((char *) envp->content, str, len) == 0)
// 			if 
// 	}
// }

// /* Creates a new string with expanded variables. Frees the old string */
// char	*expand_variables(char *str, t_token *tk_head, t_list *envp, t_ms *ms)
// {
// 	size_t	len;
// 	size_t	pos;
// 	char	*ret;

// 	len = 0;
// 	pos = 0;
// 	ret = NULL;
// 	while(str[pos] != '\0')
// 	{
// 		if (str[pos] == '$')
// 		{
// 			len += get_env_varibale_len(str + pos, envp);
// 			pos += move_pos_to_end_of_var(str + pos, envp);
// 		}
// 		else
// 			len++;
// 	}
// 	ret = create_expanded_string(str, len);
// }


// void	expand_word_token_content(t_token *tk, t_list *envp, t_ms *ms)
// {
// 	char	*str;

// 	if (tk->content == '\'')
// 	{
// 		str = copy_without_quotes();
// 		free(tk->content);
// 		tk->content = str;
// 	}
// 	else if (tk->content == '\"')
// 	{
// 		str = copy_withtout_quotes();
// 		str = expand_variables();
// 		free(tk->content);
// 		tk->content = str;
// 	}
// 	else
// 	{
// 		str = expand_variables();
// 		free(tk->content);
// 		tk->content = str;
// 	}
// }

// t_token *expander(t_token *tk, t_list *envp, t_ms *ms)
// {
// 	t_token	*cur;

// 	cur = tk;
// 	while(cur != NULL)
// 	{
// 		if (tk->type == TOKEN_WORD)
// 			expand_word_token_content(tk, envp);
// 		cur = cur->next;
// 	}
// }

// char	*create_chunk_str(char *str, t_ms *ms, char *quote)
// {
// 	size_t	len;
// 	char	quote;
// 	char	*ret;

// 	len = 0;
// 	quote = 0;
// 	while (str[len] != '\0')
// 	{
// 		if ((str[len] == '\'' || str[len] == '\"') && !*quote)
// 			*quote = str[len];
// 		else if (str[len] == quote)
// 		{
// 			COPY_INTO_RETURN_STRING();
// 			len++;
// 			break;
// 		}
// 		if (str[len] == '$' && (*quote == 0 || *quote == '\"'))
// 		{
// 			ret = str;
// 			str += len;
// 			str += expand_variable(str + len, );
// 			len = 0;
// 		}
// 		len++;
// 	}
// }


// ---------------------------------------------------------------- //

// void	copy_without_quote(char *dst, char *src, size_t size, char *quote)
// {
// 	if (src[0] == *quote && src[size - 1] == *quote)
// 		ft_strlcpy(dst, src + 1, size - 1);
// 	else if (*src == quote)
// 		ft_strlcpy(dst, src + 1, size);
// 	else if (src[size - 1] == '\'' || src[size - 1] == '\"')
// 		ft_strlcpy(dst, src, size);
// 	else
// 		ft_strlcpy(dst, src, size + 1);
// }

// // Returns the length that it scaned/moved on the original string
// size_t	create_chunk_str(char *str, t_expand *chunk, t_ms *ms, char *quote)
// {
// 	size_t	len;

// 	len = 0;
// 	while (str[len] != '\0')
// 	{
// 		if (len == 0 && str[len] == '$' && *quote != '\'') // Is first $? and expandable? Then expand and return
// 			return (expand_variable(chunk, ms, quote));
// 		if ((str[len] == '\'' || str[len] == '\"') && !*quote) // If not inside quote, save quote so we know in which quotes we are in.
// 			*quote = str[len];
// 		else if(str[len] == '$' && quote != '\'')
// 			break;
// 		if (str[len] == *quote)
// 			*quote = 0;
// 		len++;
// 	}
// 	if (len == 0 && (quote == '\"' || quote == '\''))
// 		chunk->str = ft_strdup("");
// 	else
// 		chunk->str = NULL;
// 	return (len);
// }

// size_t	create_chunk(char *str, t_expand **chunk_head, t_ms *ms, char *quote)
// {
// 	t_expand	*cur;

// 	if (*chunk_head == NULL)
// 		*chunk_head = ft_calloc(1, sizeof(t_expand));
// 			if (*chunk_head == NULL)
// 				ms_error(ms, "Malloc failed", 1, 1);
// 	cur = *chunk_head;
// 	while (cur->next != NULL)
// 		cur = cur->next;
// 	return (create_chunk_str(str, cur, ms, quote));
// }

// void	expand_word_token(t_token *token, t_ms *ms)
// {
// 	t_expand	*chunks;
// 	char		*word_str;
// 	char		quote;

// 	quote = 0;
// 	word_str = token->content;
// 	while (*word_str != '\0')
// 		word_str += create_chunk(word_str, &chunks, ms, &quote);

// }

// void	expander(t_token *tk_head, t_ms *ms)
// {
// 	t_token	*cur;

// 	cur = tk_head;
// 	while (cur != NULL)
// 	{
// 		if (cur->type == TOKEN_WORD)
// 		{
// 			check_valid_quote_count(cur);
// 			expand_word_token(cur, ms);
// 		}
// 		cur = cur->next;
// 	}
// }

// ---------------------------------------- //

/* Create and fill chunk with given str */
void	append_and_fill_chunk_with_str(t_ms *ms, const char *src, size_t len)
{
	t_expand	*chunk;

	chunk = append_chunk(ms);
	chunk->str = malloc((len + 1) * sizeof(char));
	check_if_malloc_failed((void *) chunk->str, ms);
	ft_strlcpy(chunk->str, src, len + 1);
}

/* Expands text that is not inside quotes */
void	expand_no_quotes(char **str, t_ms *ms, char *quote)
{
	size_t		len;
	char		*str_start;

	len = 0;
	str_start = *str;
	if (is_env_variable(*str))
	{
		expand_env_varible(str, ms, quote);
		return ;
	}
	while (!is_quote(*str) && !is_env_variable(*str) && **str != '\0')
	{
		len++;
		(*str)++;
	}
	append_and_fill_chunk_with_str(ms, str_start, len);
}

/* Expands text that is inside single quotes */
void	expand_single_quote_content(char **str, t_ms *ms)
{
	size_t		len;
	char		*str_start;
	// t_expand	*chunk;

	// append_chunk(ms);
	len = 0;
	(*str)++;
	str_start = *str;
	while(!is_single_quote(*str))
	{
		(*str)++;
		len++;
	}
	// if (len == 0)
	// 	return (chunk->str = ft_strdup(""), NULL);
	append_and_fill_chunk_with_str(ms, str_start, len);
	(*str)++;
}

void	expand_double_quote_content(char **str, t_ms *ms, char *prev_quote)
{
	size_t		len;
	char		*str_start;
	len = 0;
	if (is_env_variable(*str))
	{
		expand_env_varible(str, ms, prev_quote);
		return ;
	}
	if (!is_double_quote(prev_quote))
	{
		*prev_quote = '\"';
		(*str)++;
	}
	str_start = *str;
	while (!is_double_quote(*str))
	{
		if (is_env_variable(*str))
		{
			break;
			// expand_env_varible(str, ms, prev_quote);
			// return ;
		}
		len++;
		(*str)++;
	}
	append_and_fill_chunk_with_str(ms, str_start, len);
	if (is_double_quote(*str))
	{
		*prev_quote = 0;
		(*str)++;
	}
}

/* Expands all legit env variables based on there enclosing quotes
and removes all unecessary quotes */
void	expand_word_token(t_token *tk, t_ms *ms)
{
	char		*str;
	char		prev_quote;

	str = tk->content;
	prev_quote = 0;
	while (*str != '\0')
	{
		if (!is_quote(str) && !prev_quote)
			expand_no_quotes(&str, ms, &prev_quote);
		else if (is_single_quote(str) && !is_double_quote(&prev_quote))
			expand_single_quote_content(&str, ms);
		else
			expand_double_quote_content(&str, ms, &prev_quote);
	}
	// tk->content = join_chunks_to_final_word(ms);
	t_expand	*DEBUG = ms->exp;
	printf("New: ");
	while (DEBUG != NULL)
	{
		if (DEBUG->str)
			printf("%s", DEBUG->str);
		DEBUG = DEBUG->next;
	}
	printf("\n");
	free_exp(ms->exp);
	ms->exp = NULL;
}

/* Checks all lexer tokens for TOKEN_WORD, expands env variables
(if valid) and remove quotes */
void	expander(t_ms *ms)
{
	t_token	*cur;
	char	*old_string;

	cur = ms->tk;
	while (cur != NULL)
	{
		if (cur->type == TOKEN_WORD)
		{
			check_if_valid_quote_count(cur, ms);
			old_string = cur->content;
			expand_word_token(cur, ms);
			printf("Old: %s\n", old_string);
			free(old_string);
		}
		cur = cur->next;
	}
}

// typedef struct s_env
// {
// 	char	*var_name;
// 	char	*var_value;
// }				t_env;

// var_name == "a";
// var_value == "huhu";

// printf("%s=%s", var_name, var_value);