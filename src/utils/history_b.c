/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:08:20 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/27 17:26:49 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	show_history_llist(t_list **lst)
{
	int		i;
	t_list	*tmp_lst;

	tmp_lst = *lst;
	i = 0;
	while (tmp_lst)
	{
		printf("i: %i  >", i);
		c_green();
		printf("%s", (char *)tmp_lst->content);
		c_reset();
		printf("<\n");
		tmp_lst = tmp_lst->next;
		i++;
	}
}

void	limit_history_llst(t_list **history_lst)
{
	while (ft_lstsize(*history_lst) > MAX_HISTORY)
		lst_delete_first(history_lst);
}
