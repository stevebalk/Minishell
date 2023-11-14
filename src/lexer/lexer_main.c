/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:03:32 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/14 12:04:33 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

#define MAX_LINES 1000

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
		test_lines[i][ft_strlen(test_lines[i]) - 1] = '\0';
		line = get_next_line(fd);
		i++;
	}
	close(fd);
}

void	print_lexer_struct(t_token *lx)
{
	while (lx != NULL)
	{
		printf("Type: %i\n", lx->type);
		printf("String: %s\n\n", lx->content);
		lx = lx->next;
	}
}

int	main(int argc, char **argv)
{
	char	*test_lines[MAX_LINES];
	int		i;
	t_token	*lx;

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
	lx = lexer(test_lines[0]);
	print_lexer_struct(lx);
}
