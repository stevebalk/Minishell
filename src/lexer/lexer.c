/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:13:27 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/09 18:30:33 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"

void	append_token(t_token *head, t_token *new_token)
{
	t_token	*cur_token;

	cur_token = head;
	while (cur_token->next != NULL)
	{
		cur_token = cur_token->next;
	}
	cur_token->next = new_token;
}

t_token	*create_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
	// TODO Create error handling that frees everything
		exit(errno);
	token->next = NULL;
	token->type = TOKEN_EOF;
	token->str = NULL;
	return (token);
}

int	set_token_type(char *str, t_token *token)
{
	if (str[0] == '=')
		token->type = TOKEN_ASSIGN;
	else if (str[0] == '<')
	{
		if (str[1] == '<')
		{
			token->type = TOKEN_HERE_DOC;
			return (2);
		}
		else
			token->type = TOKEN_INFILE;
	}
	else if (str[0] == '>')
	{
		if (str[1] == '>')
		{
			token->type = TOKEN_REDIRECT_APPEND;
			return (2);
		}
		else
			token->type = TOKEN_REDIRECT;
	}
	else if (str[0] == '|')
		token->type = TOKEN_PIPE;
	return (1);
}

int	set_token_value(const char *str, t_token *token)
{
	int	ret;

	ret = 0;
	while (!ft_strchr(SPECIFIERS, str[ret]) || str[ret] != '\0')
		ret++;
	token->str = malloc((ret + 1) * sizeof(char));
	if (token->str == NULL)
		exit(EXIT_FAILURE); // TODO Change to proper error handling
	ft_strlcpy(token->str, str, ret);
	return (ret);
}

t_token	*lexer(char *argv)
{
	t_token	*head;
	t_token	*cur_token;

	if (*argv == '\0')
		return (NULL);
	head = create_token();
	cur_token = head;
	while (*argv != '\0')
	{
		if (ft_strchr(SPECIFIERS, **argv))
			argv += set_token_type(argv, cur_token);
		else
			argv += set_token_value(argv, cur_token);
	}
	return (head);
}

int main(int argc, char **argv)
{
	t_token	*head;
	
	head = lexer(*(argv + 1));
}
