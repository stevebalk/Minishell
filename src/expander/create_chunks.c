/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_chunk.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:42:35 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/28 15:42:53 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/* Create and fill chunk with given str */
void	append_and_fill_chunk_with_str(t_ms *ms, const char *src, size_t len)
{
	t_expand	*chunk;

	chunk = append_chunk(ms);
	chunk->str = malloc((len + 1) * sizeof(char));
	check_if_malloc_failed((void *) chunk->str, ms);
	ft_strlcpy(chunk->str, src, len + 1);
}

/* Creates a chunk with a string of size zero */
void	create_empty_string_chunk(t_ms *ms)
{
	t_expand	*chunk;

	chunk = append_chunk(ms);
	chunk->str = ft_strdup("");
	check_if_malloc_failed((void *) chunk->str, ms);
}
