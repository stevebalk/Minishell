/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:43:21 by jonas             #+#    #+#             */
/*   Updated: 2023/11/26 17:49:36 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"


/*
	with option -n (no newline)
	

	without -n:
	echo "\n" $a \n
	--> nl VAR_Value n

	\n has to be in double quotes or single quotes


	bash-3.2$ export a=huhu
	bash-3.2$ export b=\t
	bash-3.2$ export c="\t"
	==> in Export
	declare -x a="huhu"
	declare -x b="t"
	declare -x c="\\t"

*/
void builtin_echo(char **str_arr, int n_flag)
{
	int	i;
	i = -1;
	while(i++, str_arr[i])
		printf("%s", str_arr[i]);
	if (!n_flag)
		printf("\n");
}