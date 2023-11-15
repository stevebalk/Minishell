/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:01:23 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/15 17:07:36 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void find_var_in_llst(t_list **llst, char *var)
{
	t_list *tmp_lst;
    tmp_lst = *llst;

	while(tmp_lst)
	{
		/*
		ft_strcmp(var + "=", (char*)tmp_lst->content, strlen(content))
		*/
		tmp_lst = tmp_lst->next;
	}
	
	
}

/*
Todo: delete node from list (from push swap)
*/