/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_a.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:33:11 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/27 13:51:56 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	get_var_names(t_var_names *var, char *str)
{	
	//c_blue(); printf("get_var_names() string >%s<\n", str); 
	var->has_equal = has_str_symbol(str, '=');
	var->raw_copy = get_string_from_string(str);
	var->var_name = get_string_till_first_symbol(str, '=');
	var->raw_value = get_string_from_first_symbol(str, '=');
	var->value_without_quotes = get_string_without_symbols(var->raw_value, '"');
	var->value_added_quotes = get_string_with_symbols_at_end_and_front
		(var->value_without_quotes, '"');
	//c_red(); printf("get_var_names() string >%s<\n", str); 
}

// manage whole arg array; adds or update to env and export llst
void	export_arg_arr(t_list **env_llst, t_list **env_llst_sorted, char **arr)
{
	//c_yellow(); printf("export_arg_arr  \n"); c_reset();
	int	i;
	// if (!arr[0])
	// {
	// 	c_cyan(); printf("export_arg_arr  arr[0] == NULL 	  \n"); c_reset();
	// }
	
	i = -1;
	while (i++, arr[i])
		export_single_arg(env_llst, env_llst_sorted, arr[i]);

	//c_red(); printf("~export_arg_arr  \n"); c_reset();
}

// gets a single arg like "a=huhu" and adds to export and/or env if valid
void	export_single_arg(t_list **env_llst, t_list **env_llst_sorted, char *str)
{
	(void) env_llst;
	(void) env_llst_sorted;
	t_var_names	var;
	ini_var_names_to_null(&var);

	//c_yellow(); printf("export_single_arg  >%s<   \n", str); c_reset();
	if (!check_var_name(str))
	{
		//printf("export: ‘%s': not a valid identifier\n", str);	// XXX should be proper error handling; if the value is in "" there is no "" in the error message, maybe the lexar, parser solves this
		return ;
	}

	get_var_names(&var, str);
	show_var_names(&var);
	update_or_create_llst_var(env_llst, env_llst_sorted, &var);
	dealloc_var_names(&var);
	
	//c_red(); printf("~export_single_arg  >%s<   \n", str); c_reset();
}


void	update_util_env(t_list **env_llst, t_var_names *var, char *env_var_with_value)
{
	// env list
	if (find_var_in_llst(env_llst, var->var_name))
	{
		if (var->has_equal)
			update_content_in_node(find_var_in_llst(env_llst, var->var_name), env_var_with_value);
	}
	else
	{
		if (var->has_equal)
			add_variable_to_llst(env_llst, env_var_with_value);
	}
}

void	update_util_export(t_list **env_llst_sorted, t_var_names *var, char *exp_var_with_value)
{
	// exp list
	if (find_var_in_llst(env_llst_sorted, var->var_name))
	{
		if (var->has_equal)
			update_content_in_node(find_var_in_llst(env_llst_sorted, var->var_name), exp_var_with_value);
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
void	update_or_create_llst_var(t_list **env_llst, t_list **env_llst_sorted, t_var_names *var)
{
	//c_yellow(); printf("update_or_create_llst_var  >%s<   \n", var->raw_value); c_reset();

	char	*env_var_with_value;
	char	*exp_var_with_value;

	env_var_with_value = join_three_string(var->var_name, "=", var->value_without_quotes);
	exp_var_with_value = join_three_string(var->var_name, "=", var->value_added_quotes);

	update_util_env(env_llst, var, env_var_with_value);
	update_util_export(env_llst_sorted, var, exp_var_with_value);

	
	if (env_var_with_value)
		free(env_var_with_value);
	if (exp_var_with_value)
		free(exp_var_with_value);
	c_red(); printf("~export_single_arg  >%s<   \n", var->raw_value); c_reset();
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