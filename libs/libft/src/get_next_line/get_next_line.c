/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:56:13 by sbalk             #+#    #+#             */
/*   Updated: 2023/08/07 13:05:39 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	check_new_line(t_lst *node)
{
	while (node->start < node->str_len)
	{
		if (node->str[node->start] == '\n')
		{
			node->tlen++;
			node->start++;
			return (1);
		}
		node->tlen++;
		node->start++;
	}
	return (0);
}

static char	*create_new_line(t_lst *node, t_lst **stash, int fd)
{
	char	*ret;

	ret = malloc((node->tlen + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	ret[node->tlen] = '\0';
	gnl_node_to_string(ret, node);
	if (node->start == node->str_len)
	{
		gnl_free_list(stash[fd]);
		stash[fd] = NULL;
	}
	else
	{
		node->tlen = 0;
		gnl_free_list(node->next);
		node->next = NULL;
	}
	return (ret);
}

static t_lst	*create_node(char *buffer, t_lst **stash, int fd, ssize_t br)
{
	t_lst	*node;

	node = malloc(sizeof(t_lst));
	if (!node)
		return (NULL);
	node->start = 0;
	node->next = stash[fd];
	node->str = buffer;
	if (node->next)
		node->tlen = node->next->tlen;
	else
		node->tlen = 0;
	node->str_len = br;
	return (node);
}

static int	is_error(ssize_t b_read, t_lst **stash, int fd, char *buffer)
{
	if (b_read <= 0)
	{
		free(buffer);
		if (b_read == 0)
		{
			if (stash[fd])
				return (2);
		}
		else if (b_read == -1)
		{
			if (stash[fd])
				stash[fd] = gnl_free_list(stash[fd]);
		}
		return (1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static t_lst	*stash[4096];
	char			*buffer;
	int				is_new_line;
	ssize_t			bytes_read;
	int				error;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	is_new_line = 0;
	if (stash[fd])
		is_new_line = check_new_line(stash[fd]);
	while (!is_new_line)
	{
		buffer = malloc(BUFFER_SIZE * sizeof(char));
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		error = is_error(bytes_read, stash, fd, buffer);
		if (error == 2)
			break ;
		else if (error)
			return (NULL);
		stash[fd] = create_node(buffer, stash, fd, bytes_read);
		is_new_line = check_new_line(stash[fd]);
	}
	return (create_new_line(stash[fd], stash, fd));
}
