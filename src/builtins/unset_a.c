/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:01:23 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/16 13:46:04 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

t_list *find_var_in_llst(t_list **llst, char *var)
{
	t_list *tmp_lst;
    tmp_lst = *llst;

	while(tmp_lst)
	{
		//char c = (char*)(tmp_lst->content)[ft_strlen(var)+1];
		char *tmp_str;
		tmp_str = (char*)tmp_lst->content;
		
		if ((ft_strcmp(var, (char*)tmp_lst->content, ft_strlen(var)) == 0) && (tmp_str[ft_strlen(var)+1] == '='))
		{
			c_red(); printf("-> found >%s< with = \n", var);
			c_purple(); printf("->%s< \n", tmp_str);
			break;
		}

		
		
		tmp_lst = tmp_lst->next;
	}
	
	
}

/*
Todo: delete node from list (from push swap)
*/