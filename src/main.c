/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:12:12 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/23 16:14:36 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

void test_var_names(t_list	*env_llst, t_list	*env_llst_sorted)
{
	c_yellow(); printf("test_var_names()\n"); c_reset();

	// char *tmp1 = "a=huhu";
	// char *tmp2 = "_a=\"huhu\"";
	// char *tmp3 = "_9a=huhu";
	// char *tmp4 = "9_a=huhu";
	// char *tmp5 = "9=huhu";
	char *tmp6 = "c";
	char *tmp7 = "d=gg";
	char *tmp8 = "d=88";




	// printf("check >%s<  valid: %i \n", tmp1, check_var_name(tmp1));
	// printf("check >%s<  valid: %i \n", tmp2, check_var_name(tmp2));
	// printf("check >%s<  valid: %i \n", tmp3, check_var_name(tmp3));
	// printf("check >%s<  valid: %i \n", tmp4, check_var_name(tmp4));
	// printf("check >%s<  valid: %i \n", tmp5, check_var_name(tmp5));
	printf("check >%s<  valid: %i \n", tmp6, check_var_name(tmp6));
	printf("check >%s<  valid: %i \n", tmp7, check_var_name(tmp7));


	// export_single_arg(NULL, NULL, tmp1);
	// export_single_arg(NULL, NULL, tmp2);
	// export_single_arg(NULL, NULL, tmp3);
	// export_single_arg(NULL, NULL, tmp4);
	// export_single_arg(NULL, NULL, tmp5);
	export_single_arg(&env_llst, &env_llst_sorted, tmp6);
	export_single_arg(&env_llst, &env_llst_sorted, tmp7);

	c_purple(); printf("############################################\n");

	export_single_arg(&env_llst, &env_llst_sorted, tmp6);
	export_single_arg(&env_llst, &env_llst_sorted, tmp8);

}


int	main(int argc, char **argv, char **env)
{
	t_list	*hist_llst;
	t_list	*env_llst;
	t_list	*env_llst_sorted;

	hist_llst = NULL;
	env_llst = NULL;
	env_llst_sorted = NULL;
	(void)argc;
	(void)argv;
	(void)env;
	(void)hist_llst;
	// (void)env_llst;
	// (void)env_llst_sorted;
	

	// signal(SIGINT, handle_sigint);
	//show_env_arr(*env);
	load_env_to_llst(&env_llst, env);
	copy_llst(&env_llst, &env_llst_sorted);
	
	test_var_names(env_llst, env_llst_sorted );


	show_env_llist(&env_llst);
	sort_list(env_llst_sorted);
	show_env_llist(&env_llst_sorted);

	char *tmp_del = get_val_of_var(&env_llst_sorted, "d");
	printf("tmp_del >%s<\n", tmp_del);
	free(tmp_del);

	// history_master(&hist_llst);
	// prompt_handler(&hist_llst, &env_llst, &env_llst_sorted);
	// lst_dealloc(&hist_llst, 1);
	lst_dealloc(&env_llst, 1);
	lst_dealloc(&env_llst_sorted, 1);
	c_red();
	printf("~main ()\n");
	c_reset();
	return (0);
}
