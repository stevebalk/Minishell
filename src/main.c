/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:12:12 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/28 19:25:25 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"



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

	load_env_to_llst(&env_llst, env);
	copy_llst(&env_llst, &env_llst_sorted);
	show_env_llist(&env_llst);
	
	//history_master(&hist_llst);
	//prompt_handler(&hist_llst, &env_llst, &env_llst_sorted);

	test_getcwd();
	test_opendir();
	test_is_dir_valid("libs");
	builtin_pwd(&env_llst, &env_llst_sorted, 1);
	
	builtin_cd(&env_llst, &env_llst_sorted, "src");
	
	show_env_llist(&env_llst);
	
	lst_dealloc(&hist_llst, 1);
	lst_dealloc(&env_llst, 1);
	lst_dealloc(&env_llst_sorted, 1);
	c_red();
	printf("~main ()\n");
	c_reset();
	return (0);
}
