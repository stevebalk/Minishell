/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:13:27 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/10 00:12:06 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

#define MAX_LINES 1000

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

// int	set_special_token(char *str, t_token *token)
// {
// 	if (str[0] == '=')
// 		token->type = TOKEN_ASSIGN;
// 	else if (str[0] == '<')
// 	{
// 		if (str[1] == '<')
// 		{
// 			token->type = TOKEN_HERE_DOC;
// 			return (2);
// 		}
// 		else
// 			token->type = TOKEN_INFILE;
// 	}
// 	else if (str[0] == '>')
// 	{
// 		if (str[1] == '>')
// 		{
// 			token->type = TOKEN_REDIRECT_APPEND;
// 			return (2);
// 		}
// 		else
// 			token->type = TOKEN_REDIRECT;
// 	}
// 	else if (str[0] == '|')
// 		token->type = TOKEN_PIPE;
// 	return (1);
// }

int	set_special_token(char *str, t_token *token)
{
	int	ret;

	ret = 1;
	if (str[0] == '=')
		token->type = TOKEN_ASSIGN;
	if (str[0] == '<')
		token->type = TOKEN_INFILE;
	if (str[1] == '<' && token->type == TOKEN_INFILE)
	{
		token->type = TOKEN_HERE_DOC;
		ret++;
	}
	if (str[0] == '>')
		token->type = TOKEN_REDIRECT;
	if (str[1] == '>' && token->type == TOKEN_REDIRECT)
	{
		token->type = TOKEN_REDIRECT_APPEND;
		ret++;
	}
	if (str[0] == '|')
		token->type = TOKEN_PIPE;
	token->str = malloc((ret + 1) * sizeof(char));
	if (token->str == NULL)
		exit(EXIT_FAILURE); // TODO: Implement proper error handling
	ft_strlcpy(token->str, str, ret + 1);
	return (ret);
}

int	set_word_token(const char *str, t_token *token)
{
	int	ret;

	ret = 0;
	while (!ft_strchr(TOKEN_TYPES, str[ret]) && str[ret] != '\0')
		ret++;
	token->str = malloc((ret + 1) * sizeof(char));
	if (token->str == NULL)
		exit(EXIT_FAILURE); // TODO: Implement proper error handling
	ft_strlcpy(token->str, str, ret + 1);
	return (ret);
}

t_token	*lexer(char *str)
{
	t_token	*head;
	t_token	*cur_token;

	if (*str == '\0')
		return (NULL);
	head = create_token();
	cur_token = head;
	while (*str != '\0')
	{
		if (ft_strchr(TOKEN_TYPES, *str))
			str += set_special_token(str, cur_token);
		else
			str += set_word_token(str, cur_token);
	}
	return (head);
}

/* TEST FUNCTION DELETE LATER */
void	read_test_file(char **filename, char *test_lines[100])
{
	int		fd;
	char	*line;
	int		i;

	line = NULL;
	i = 0;
	fd = open(*filename, O_RDONLY, 0644);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(errno);
	}
	line = get_next_line(fd);
	while (line != NULL && i < MAX_LINES)
	{
		test_lines[i] = line;
		line = get_next_line(fd);
		i++;
	}
	close(fd);
}

int main(int argc, char **argv)
{
	char	*test_lines[MAX_LINES];
	int		i;


	t_token	*head;
	i = 0;
	if (argc == 2)
	{
		if (access(argv[1], F_OK) == 0)
			read_test_file(argv + 1, test_lines);
		else
		{
			perror("File doesn't exist");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		printf("Wrong input. Use: ./lexer <test_file>\n");
		printf("Testfile should be filled with bash commands");
		exit(EXIT_FAILURE);
	}
	while (test_lines[i] != NULL)
	{
		printf("%s\n", test_lines[0]);
		i++;
	}
	head = lexer(test_lines[0]);
	printf("%s", head->str);
}
