/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:03:32 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/27 16:02:24 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MAX_LINES 1000

/* TEST FUNCTION DELETE LATER */
void	read_test_file(char **filename, char *test_lines[100])
{
	int		fd;
	char	*line;
	// int		i;

	line = NULL;
	// i = 0;
	fd = open(*filename, O_RDONLY, 0644);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(errno);
	}
	line = get_next_line(fd);
	test_lines[0] = line;
	test_lines[0][ft_strlen(test_lines[0]) - 1] = '\0';
	// while (line != NULL && i < MAX_LINES)
	// {
	// 	test_lines[i] = line;
	// 	test_lines[i][ft_strlen(test_lines[i]) - 1] = '\0';
	// 	line = get_next_line(fd);
	// 	i++;
	// }
	close(fd);
}

void	print_lexer_struct(t_token *tk)
{
	while (tk != NULL)
	{
		// printf("prev: %p\n", tk->prev);
		printf("Type: %i\n", tk->type);
		printf("String: %s\n", tk->content);
		// printf("Join: %d\n", tk->join);
		// printf("Cur:  %p\n", tk);
		printf("\n");
		tk = tk->next;
	}
}

int	main(int argc, char **argv)
{
	char	*test_lines[MAX_LINES];
	t_ms	ms;

	ms = (t_ms){NULL, NULL, NULL, NULL, "127"};

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
		printf("Testfile should be filled with bash commands\n");
		exit(EXIT_FAILURE);
	}
	ms.tk = lexer(test_lines[0]);
	print_lexer_struct(ms.tk);
	expander(&ms);
	print_lexer_struct(ms.tk);
	char *args[] = {NULL, NULL, NULL};
	args[0] = ms.tk->content;
	args[1] = ms.tk->next->content;
	execv("/bin/cat", args);
	perror("execv");
	ms_error(&ms, NULL, 0, 0);
	free(test_lines[0]);
}
