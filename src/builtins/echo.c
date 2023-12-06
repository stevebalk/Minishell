/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:43:21 by jonas             #+#    #+#             */
/*   Updated: 2023/12/06 18:18:53 by jonas            ###   ########.fr       */
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


void	test_parser_echo(t_list **env_llst, t_list **env_llst_sorted,
			char *str)
{
	(void)env_llst;
	(void)env_llst_sorted;
	char **arr;
	arr = ft_split(str, ' ');
	
	if (ft_strncmp("echo", str, 4) == 0 && ft_strlen(str) == 4) 
	{
		//builtin_echo(NULL, 0);
	}
	else if (ft_strncmp("echo", str, 4) == 0 && ft_strlen(str) > 5) 
	{
		builtin_echo(arr, 0);			// very rough implementation
	}

	free(arr);
}

void	builtin_echo(char **str_arr, int n_flag)
{
	int	i;
	c_yellow(); printf("builtin_echo   >%s<  >%s<\n", str_arr[0], str_arr[1]); c_reset();
	
	i = 0;		// skip first entry for a quick test; has to be reworked in combination with executer stuff
	while (i++, str_arr[i])
	{
		if (ft_strncmp(str_arr[i], "$$", 2) == 0)
		{
			// PID print
			/* Todo: Finding a way to get the pid of our minishell */
			int pid = getpid();
			printf("PID: %i     >> XXX use another command, because getPid is not allowed\n", pid);
		}
		else
			printf("%s", str_arr[i]);
	}
	if (!n_flag)
		printf("\n");

	c_red(); printf("~builtin_echo \n");
}
