/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:43:55 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/29 13:32:50 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	ms_exit(char *arg)
{
	(void)arg;
	/*
	free everything
	*/

	return (0);
}

/*
BASH
exit 		--> exits the bash

exit a		--> exits the bash, but with error
exit
bash: exit: a: numeric argument required

exit 1		--> exits the bash with exit code

bash-3.2$ exit (1)		--> NO exit but error
bash: syntax error near unexpected token `1'

bash-3.2$ exit "1"		--> exits without error and with exit code 1
exit

bash-3.2$ exit 1 2		--> no Exit
exit
bash: exit: too many arguments
*/