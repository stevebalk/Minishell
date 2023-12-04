/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 17:54:15 by jonas             #+#    #+#             */
/*   Updated: 2023/12/04 17:05:30 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include "../../include/minishell.h"


// test parse for cd ~ and cd -
void	test_parser_cd_pwd_home(t_ms *ms, t_list **env_llst, t_list **env_llst_sorted, char *str)
{
	if (ft_strncmp("cd", str, 2) == 0 && ft_strlen(str) >= 2) // change dir 
		builtin_cd(ms, env_llst, env_llst_sorted, str + 3);

	if (ft_strncmp("pwd", str, 3) == 0 && ft_strlen(str) == 3) // print pwd
		builtin_pwd(env_llst, env_llst, 1);
	if (ft_strncmp("clear", str, 5) == 0) // print pwd
		clear_screen();
}


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
		//export_arg(env_llst, env_llst_sorted, str, 7); // old not existing anymore
	}
	else if (ft_strncmp("env", str, 3) == 0 && ft_strlen(str) == 3)	// shows env list
		show_env_llist(env_llst);
}

void test_var_names(t_list	*env_llst, t_list	*env_llst_sorted)
{
	c_yellow(); printf("test_var_names()\n"); c_reset();

	// char *tmp1 = "a=huhu";
	// char *tmp2 = "_a=\"huhu\"";
	// char *tmp3 = "_9a=huhu";
	// char *tmp4 = "9_a=huhu";
	char *tmp5 = "dd=huhu";
	char *tmp6 = "c";
	char *tmp7 = "d=gg";
	char *tmp8 = "d=88";




	// printf("check >%s<  valid: %i \n", tmp1, check_var_name(tmp1));
	// printf("check >%s<  valid: %i \n", tmp2, check_var_name(tmp2));
	// printf("check >%s<  valid: %i \n", tmp3, check_var_name(tmp3));
	// printf("check >%s<  valid: %i \n", tmp4, check_var_name(tmp4));
	printf("check >%s<  valid: %i \n", tmp5, check_var_name(tmp5));
	printf("check >%s<  valid: %i \n", tmp6, check_var_name(tmp6));
	printf("check >%s<  valid: %i \n", tmp7, check_var_name(tmp7));


	// export_single_arg(NULL, NULL, tmp1);
	// export_single_arg(NULL, NULL, tmp2);
	// export_single_arg(NULL, NULL, tmp3);
	// export_single_arg(NULL, NULL, tmp4);
	export_single_arg(&env_llst, &env_llst_sorted, tmp5);
	export_single_arg(&env_llst, &env_llst_sorted, tmp6);
	export_single_arg(&env_llst, &env_llst_sorted, tmp7);

	c_purple(); printf("############################################\n");

	export_single_arg(&env_llst, &env_llst_sorted, tmp6);
	export_single_arg(&env_llst, &env_llst_sorted, tmp8);

}

void test_export_arg_array(t_list	*env_llst, t_list	*env_llst_sorted)
{
	c_yellow(); printf("test_export_arg_array()\n"); c_reset();
	char *arr[1] = {NULL};
	//char *arr[4] = {"huhu", "moin", "Steve=huhu", NULL};
	export_arg_arr(&env_llst, &env_llst_sorted, arr);
}

void test_get_val_of_var(t_list	*env_llst, t_list	*env_llst_sorted)
{
	(void)env_llst;
	//c_yellow(); printf("test_get_val_of_var()\n"); c_reset();
	char *tmp_del = get_val_of_var(&env_llst_sorted, "d");
	//printf("tmp_del >%s<\n", tmp_del);
	free(tmp_del);
}

void test_echo(void)
{
	c_yellow(); printf("test_echo()\n"); c_purple();
	char *arr[4] = {"huhu", "\t", "Steve", NULL};
	builtin_echo(arr, 0);
	c_reset();
}