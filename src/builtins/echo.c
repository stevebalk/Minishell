/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:43:21 by jonas             #+#    #+#             */
/*   Updated: 2023/12/06 13:48:09 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

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

/*
echo $$			--> PID of the shell
echo $?			--> last exit code
echo $#			--> number of positional parameters		--> return 0; only makes sense in a script or when set arguments before
echo $*, $@		--> All positional parameters	--> only makes sense in a script or when set arguments before
echo $!			--> Process ID of the last background command.


*/
void	builtin_echo(char **str_arr, int n_flag)
{
	int	i;

	i = -1;
	while (i++, str_arr[i])
		printf("%s", str_arr[i]);
	if (!n_flag)
		printf("\n");
}
