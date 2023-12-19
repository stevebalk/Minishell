/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_a.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:33:11 by jopeters          #+#    #+#             */
/*   Updated: 2023/12/19 14:09:59 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
	
// manage whole arg array; adds or update to env and export llst
int	export_arg_arr(t_list **env_llst, t_list **env_llst_sorted, char **arr)
{
	//c_yellow(); printf("export_arg_arr  \n"); c_reset();
	int	i;
	int arr_len;
	int	exit_code;
	exit_code = 0;
	// if (!arr[0])
	// {
	// 	c_cyan(); printf("export_arg_arr  arr[0] == NULL 	  \n"); c_reset();
	// }
	arr_len = 0;
	while (arr[arr_len])
		arr_len++;
	
	//c_cyan(); printf("export_arg_arr   arr_len: %i  \n", arr_len); c_reset();
	if (arr_len == 1)
	{
		sort_list(*env_llst_sorted);
		show_env_llist(env_llst_sorted);
	}
	
	i = 0;
	while (i++, arr_len > 1 && arr[i])
		exit_code = export_single_arg(env_llst, env_llst_sorted, arr[i]);
	//c_red(); printf("~export_arg_arr  \n"); c_reset();
	return (exit_code);
}

// gets a single arg like "a=huhu" and adds to export and/or env if valid
int	export_single_arg(t_list **env_llst, t_list **env_llst_sorted, char *str)
{
	t_var_names	var;
	//int	exit_code;
	
	(void) env_llst;
	(void) env_llst_sorted;

	//exit_code = 0;

	ini_var_names_to_null(&var);
	//c_yellow(); printf("export_single_arg  >%s<   \n", str); c_reset();
	if (!check_var_name(str))
	{
		//printf("export: ‘%s': not a valid identifier\n", str);	// XXX should be proper error handling; if the value is in "" there is no "" in the error message, maybe the lexar, parser solves this
		printf("minishell: export: ‘%s': not a valid identifier\n", str);
		return (1);
	}
	get_var_names(&var, str);
	//show_var_names(&var);
	update_or_create_llst_var(env_llst, env_llst_sorted, &var);
	dealloc_var_names(&var);
	//c_red(); printf("~export_single_arg  >%s<   \n", str); c_reset();
	return (0);
}

// belongs to update_util_export
void	update_util_env(t_list **env_llst, t_var_names *var,
	char *env_var_with_value)
{
	if (find_var_in_llst(env_llst, var->var_name))
	{
		if (var->has_equal)
			update_content_in_node(find_var_in_llst(env_llst, var->var_name),
				env_var_with_value);
	}
	else
	{
		if (var->has_equal)
			add_variable_to_llst(env_llst, env_var_with_value);
	}
}

// belongs to update_util_export
void	update_util_export(t_list **env_llst_sorted, t_var_names *var,
	char *exp_var_with_value)
{
	if (find_var_in_llst(env_llst_sorted, var->var_name))
	{
		if (var->has_equal)
			update_content_in_node(find_var_in_llst(env_llst_sorted,
					var->var_name), exp_var_with_value);
	}
	else
	{
		if (var->has_equal)
			add_variable_to_llst(env_llst_sorted, exp_var_with_value);
		else
			add_variable_to_llst(env_llst_sorted, var->var_name);
	}
}

// simple function to manage env and export list
void	update_or_create_llst_var(t_list **env_llst,
	t_list **env_llst_sorted, t_var_names *var)
{
	char	*env_var_with_value;
	char	*exp_var_with_value;

	//c_yellow(); printf("update_or_create_llst_var  >%s<   \n", var->raw_value); c_reset();
	env_var_with_value = join_three_string(var->var_name, "=",
			var->value_without_quotes);
	exp_var_with_value = join_three_string(var->var_name, "=",
			var->value_added_quotes);
	update_util_env(env_llst, var, env_var_with_value);
	update_util_export(env_llst_sorted, var, exp_var_with_value);
	if (env_var_with_value)
		free(env_var_with_value);
	if (exp_var_with_value)
		free(exp_var_with_value);
	//c_red(); printf("~export_single_arg  >%s<   \n", var->raw_value); c_reset();
}


//void export_master()

/*
BASH

export a=huhu  --> in export a="huhu"   in env a=huhu

bash-3.2$ export b ="moin"
bash: export: `=moin': not a valid identifier

export c='"moin"'		 --> in export c="\"moin\"" in env c="moin"
export d="huhu weiter "  --> in export d="huhu weiter "  in env d=huhu weiter | ohne die pipe aber mit leerzeichen 


export a=		--> kein Fehler;
a=""			in Export
a=				in env

export b		--> kein Fehler, aber nichts in ENV!
b				in Export


export d = huhu		--> fehler, aber er legt d und huhu an
bash: export: `=': not a valid identifier
d				in export
huhu			in export

export 9="huhu"
bash: export: `9=huhu': not a valid identifier

bash-3.2$ export 9=huhu
bash: export: `9=huhu': not a valid identifier

*/