/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_a.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:33:11 by jopeters          #+#    #+#             */
/*   Updated: 2024/01/05 20:24:35 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

// manage whole arg array; adds or update to env and export llst
int	exp_arg_arr(t_list **env_llst, t_list **env_llst_sorted, char **arr)
{
	int	i;
	int	arr_len;
	int	exit_code;

	exit_code = 0;
	arr_len = 0;
	while (arr[arr_len])
		arr_len++;
	if (arr_len == 1)
	{
		sort_list(*env_llst_sorted);
		show_export_llist(env_llst_sorted);
	}
	i = 0;
	while (i++, arr_len > 1 && arr[i])
		exit_code = export_single_arg(env_llst, env_llst_sorted, arr[i]);
	return (exit_code);
}

// gets a single arg like "a=huhu" and adds to export and/or env if valid
int	export_single_arg(t_list **env_llst, t_list **env_llst_sorted, char *str)
{
	t_var_names	var;

	(void) env_llst;
	(void) env_llst_sorted;
	ini_var_names_to_null(&var);
	if (!check_var_name(str))
	{
		c_red();
		fflush(stdout);
		ft_putstr_fd("minishell: export: ‘", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd("'", STDERR_FILENO);
		ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
		return (1);
	}
	get_var_names(&var, str);
	update_or_create_llst_var(env_llst, env_llst_sorted, &var);
	dealloc_var_names(&var);
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
}
