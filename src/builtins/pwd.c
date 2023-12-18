/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:40:32 by jopeters          #+#    #+#             */
/*   Updated: 2023/12/18 17:43:47 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

void builtin_pwd(t_list **env_llst, t_list **env_llst_sorted, int print_pwd)
{
	//c_yellow(); printf("builtin_pwd()\n"); c_reset();

	char *buffer;
	char *pwd;
    size_t size = 1024;
	(void)env_llst;
	(void)env_llst_sorted;

    buffer = (char *)malloc(size * sizeof(char));
    if (buffer == NULL) 
	{
        perror("Unable to allocate buffer");
        exit(1);
    }

	if (getcwd(buffer, size) == NULL) 
	{
        perror("Error getting current directory");
        exit(1);
	}

	if (print_pwd)
	{
		c_green();
		printf("%s\n", buffer);
	}
	
	pwd = join_three_string("PWD", "=", buffer);
	if (env_llst && env_llst)
		export_single_arg(env_llst, env_llst_sorted, pwd);

    // Free the allocated memory
	free(pwd);
    free(buffer);
}
