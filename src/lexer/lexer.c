/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:13:27 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/09 11:52:51 by sbalk            ###   ########.fr       */
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
	token->value = NULL;
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

void	lexer(char **argv, t_token *head)
{
	int	pos;
	t_token	*cur_token;

	pos = 0;
	cur_token = head;
	while (argv[1][pos] != '\0')
	{
		if (ft_strchr(SPECIFIERS, **argv))
			pos += set_token_type(&argv[1][0], cur_token);
		else
		{
			
		}
	}
}

int main(int argc, char **argv)
{
	t_token	head;

	fill_default_token(&head);
	lexer(argv, &head);

}
