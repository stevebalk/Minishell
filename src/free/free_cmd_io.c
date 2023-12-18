/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:33:51 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/18 15:07:36 by sbalk            ###   ########.fr       */
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
		// if (cur->input)
		// 	free(cur->input);
		// if (cur->output)
		// 	free(cur->output);
		// if (cur->command_arr)
		// 	ft_free_array((void **) cur->command_arr);
		cur->command_arr = NULL;
		free(cur);
		cur = next;
	}
	*list = NULL;
}
