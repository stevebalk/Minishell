/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_a.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:22:48 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/14 13:43:15 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void show_env_arr(char **env)
{
	int i;
	i = -1;
	while(i++, env[i])
		printf("i: %i  >%s<\n", i, env[i]);
}

void load_env(t_list **env_lst, char **env)
{
	(void)env_lst;
	(void)env;
/*



*/

	
}