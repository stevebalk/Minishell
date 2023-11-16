/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:01:23 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/16 23:23:59 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void test_parser_unset(t_list **env_llst, t_list **env_llst_sorted, char *str)
{
	(void)env_llst;
	(void)env_llst_sorted;
	
	if (ft_strncmp("unset", str, 5) == 0 && ft_strlen(str) > 5)
	{
		c_purple();printf("start searching variable\n");c_reset();
		delete_node_from_llst(env_llst_sorted, find_var_in_llst(env_llst_sorted, str+6));
	}
	
}

t_list *find_var_in_llst(t_list **llst, char *var)
{
	t_list *tmp_lst;
	char *tmp_str;
	
    tmp_lst = *llst;
	c_yellow(); printf("find_var_in_llst() --> var >%s<\n", var); c_reset();
	while(tmp_lst)
	{
		tmp_str = (char*)tmp_lst->content;
		printf("content >%s< strlen + 1 >%c<    len: %i      match: %i\n ", tmp_str, tmp_str[(ft_strlen(var))], (int)ft_strlen(var), ft_strncmp(var, (char*)tmp_lst->content, ft_strlen(var)) );

		if ((ft_strncmp(var, (char*)tmp_lst->content, ft_strlen(var)) == 0) && (tmp_str[ft_strlen(var)] == '='))
		{
			c_red(); printf("-> found >%s< with = \n", var);
			c_purple(); printf("->%s< \n", tmp_str);
			free(tmp_str);
			return tmp_lst;
			break;
		}

		
		
		tmp_lst = tmp_lst->next;
	}
	
	return NULL;
	
}

/*
Todo: delete node from list (from push swap)
*/