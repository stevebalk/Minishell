/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:26:39 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/06 18:41:41 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executer(t_ms *ms)
{
	if (!ms->cmd)
		return ;
}

/*
Jonas Überlegungen

Pro Command:
1x fork

wenn mehr als 1 command --> pipe
pro Pipe braucht mein ein int fd[2] array

alle commands können bzw. müssen hintereinander ablaufen

Executer:
1. zählt die commands
2. zählt die pipes

3. calloc pids für die forks
4. calloc fd[2] für pipe

Schleife für alle Commands
	execute_single(t_command  command);
	
	wenn es einen weiteren command gibt
		--> out FD in den nächsten in FD schreiben


*/