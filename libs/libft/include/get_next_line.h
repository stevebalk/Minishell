/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:56:23 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/25 15:05:33 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_lst
{
	char			*str;
	size_t			str_len;
	size_t			start;
	size_t			tlen;
	struct s_lst	*next;
}	t_lst;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

char	*get_next_line(int fd);
void	gnl_node_to_string(char *str, t_lst *node);
t_lst	*gnl_free_list(t_lst *node);

#endif