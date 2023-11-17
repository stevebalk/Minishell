/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:01:23 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/17 17:32:25 by jopeters         ###   ########.fr       */
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
		delete_node_from_llst(env_llst, find_var_in_llst(env_llst, str+6));
	}
	
}

// finds var in llst and returns the node
t_list *find_var_in_llst(t_list **llst, char *var)
{
	t_list *tmp_lst;
	char *tmp_str;
	
    tmp_lst = *llst;
	c_yellow(); printf("find_var_in_llst() --> var >%s<\n", var); c_reset();
	while(tmp_lst)
	{
		tmp_str = (char*)tmp_lst->content;
		//printf("content >%s< char >%c<    len: %i      match: %i\n ", tmp_str, tmp_str[(ft_strlen(var))], (int)ft_strlen(var), ft_strncmp(var, (char*)tmp_lst->content, ft_strlen(var)) );

		if ((ft_strncmp(var, (char*)tmp_lst->content, ft_strlen(var)) == 0) && (tmp_str[ft_strlen(var)] == '='))
		{
			c_green(); printf("  -> found var >%s< with = \n", var);
			c_purple(); printf("  -> content >%s< \n", tmp_str);
			return tmp_lst;
			break;
		}
		tmp_lst = tmp_lst->next;
	}
	c_red(); printf("~find_var_in_llst() --> not found >%s<\n", var); c_reset();
	return NULL;
	
}

// updates the content of a node 
void update_content_in_node(t_list *node, char *new_content)
{
	c_yellow(); printf("update_content_in_node() --> new_content >%s<   node->conten >%s<\n", new_content, (char*)node->content); c_reset();

	if (node && node->content)
		free(node->content);
	else
		return;
	node->content = (char *)malloc(sizeof(char) * (ft_strlen(new_content) + 1));
	ft_strlcpy(node->content, new_content, ft_strlen(new_content) + 1);
}


/*

Todo:
export a="huhu"

vorher checken ob schon vorhanden
wenn vorhanden dann content freen 
und neuen Inhalt hinzufügen


*/
