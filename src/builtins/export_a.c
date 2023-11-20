/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_a.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:33:11 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/20 16:25:01 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

// shows sorted env list when typing "export", 
void	test_parser_export(t_list **env_llst, t_list **env_llst_sorted, char *str)
{
	//char	*clean_var_no_equal;
	//char	*tmp_string_no_quotes;
	if (ft_strncmp("export", str, 6) == 0 && ft_strlen(str) == 6) // Export  || sort and show list
	{
		sort_list(*env_llst_sorted);
		show_env_llist(env_llst_sorted);
	}
	else if (ft_strncmp("export", str, 6) == 0 && ft_strlen(str) > 6) // Export A="huhu" || adds variable to list
	{
		export_arg(env_llst, env_llst_sorted, str);
		
		// c_cyan(); printf("test_parser_export  add variable  >%s<   len: %i \n", str, (int)ft_strlen(str)); c_reset();
		// clean_var_no_equal = get_string_till_first_symbol(str+7, '=');
		// tmp_string_no_quotes = get_string_without_symbols(str+7, '"');
		// printf(" --> clean var name >%s<\n", clean_var_no_equal);
		// // Check if variable is there if not add variable
		// if (find_var_in_llst(env_llst, clean_var_no_equal))
		// {
		// 	update_content_in_node(find_var_in_llst(env_llst, clean_var_no_equal), str + 7);
		// 	update_content_in_node(find_var_in_llst(env_llst_sorted, clean_var_no_equal), tmp_string_no_quotes);
		// }
		// else
		// {
		// 	add_variable_to_llst(env_llst, str + 7);
		// 	add_variable_to_llst(env_llst_sorted, tmp_string_no_quotes);
		// }

		// free(clean_var_no_equal);
		// free(tmp_string_no_quotes);
	}
	else if (ft_strncmp("env", str, 3) == 0 && ft_strlen(str) == 3)	// shows env list
		show_env_llist(env_llst);
}

// adds/updates a variable to export and env
void export_arg(t_list **env_llst, t_list **env_llst_sorted, char *str)
{
	char	*clean_var_no_equal;
	char	*tmp_string_no_quotes;

	c_cyan(); printf("export_arg  add variable  >%s<   \n", str); c_reset();
	clean_var_no_equal = get_string_till_first_symbol(str+7, '=');
	tmp_string_no_quotes = get_string_without_symbols(str+7, '"');
	printf(" --> clean var name >%s<\n", clean_var_no_equal);
		// Check if variable is there if not add variable
	if (find_var_in_llst(env_llst, clean_var_no_equal))
	{
		update_content_in_node(find_var_in_llst(env_llst, clean_var_no_equal), str + 7);
		update_content_in_node(find_var_in_llst(env_llst_sorted, clean_var_no_equal), tmp_string_no_quotes);
	}
	else
	{
		add_variable_to_llst(env_llst, str + 7);
		add_variable_to_llst(env_llst_sorted, tmp_string_no_quotes);
	}

	free(clean_var_no_equal);
	free(tmp_string_no_quotes);
}


//void export_master()

/*
BASH

export a=huhu  --> in export a="huhu"   in env a=huhu

bash-3.2$ export b ="moin"
bash: export: `=moin': not a valid identifier

export c='"moin"'		 --> in export c="\"moin\"" in env c="moin"
export d="huhu weiter "  --> in export d="huhu weiter "  in env d=huhu weiter | ohne die pipe aber mit leerzeichen 
*/