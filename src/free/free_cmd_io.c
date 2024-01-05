/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:33:51 by sbalk             #+#    #+#             */
/*   Updated: 2024/01/05 10:31:51 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_io_list(t_cmd_io **list)
{
	t_cmd_io	*cur;
	t_cmd_io	*next;

	if (list == NULL || *list == NULL)
		return ;
	cur = *list;
	while (cur != NULL)
	{
		next = cur->next;
		cur->command_arr = NULL;
		free(cur);
		cur = next;
	}
	*list = NULL;
}
