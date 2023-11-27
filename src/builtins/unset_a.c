/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:01:23 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/27 14:04:51 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	test_parser_unset(t_list **env_llst,
			t_list **env_llst_sorted, char *str)
{
	if (ft_strncmp("unset", str, 5) == 0 && ft_strlen(str) > 5)
	{
		//c_purple();printf("start searching variable\n");c_reset();
		delete_node_from_llst(env_llst_sorted,
			find_var_in_llst(env_llst_sorted, str + 6));
		delete_node_from_llst(env_llst, find_var_in_llst(env_llst, str + 6));
	}
}


/*
export a="huhu"   // creates a var named a with value huhu in env and "huhu" in export
unset a="huhu"    // bash: unset: `a=huhu': not a valid identifier
unset a 		  // deleted a and value in export and env
unset			  // does nothing
unset .			  // bash: unset: `.': not a valid identifier
unset cc		  // macht nicht wenn cc vorher nicht angelegt worden ist
*/