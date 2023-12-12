/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:26:39 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/12 14:07:28 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_file(t_ms *ms, t_redir *redir)
{
	char *tokenTypeNames[] = {
		"WORD",
		"PIPE",
		"REDIRECT",
		"REDIRECT_APPEND",
		"INFILE",
		"HERE_DOC",
		"VARIABLE",
		"EOF"
	};
	c_yellow(); printf("check_file() \n");
	t_redir *tmp_redir;
	int		fd;

	if (!redir)
		return ;

	tmp_redir = redir;	
	
	// open every file and printf error if needed
	while (tmp_redir)
	{
		c_blue();printf("    Type:");c_purple();			printf(" %s", tokenTypeNames[tmp_redir->type]);
		c_blue();printf(" Filename: ");c_purple();printf("%s\n", tmp_redir->target);c_reset();

		// Check Infile
		if (tmp_redir->type == TOKEN_INFILE)
		{
			fd = open(tmp_redir->target, O_RDONLY, 0644);
			printf("\t  open IN file >%s< \n", tmp_redir->target);
			if (fd == -1)
			{
				c_red(); printf("\t\tError 1 --> TODO Error Handling Open in file in check_file \nCancel EXECUTION"); c_reset();
				ms->last_exit_code_int = 1; 			// richtiger Code?
			}
			else
			{
				c_green(); printf("\t\tFD: %i   --> TODO Error Handling Open in file in check_file \n", fd); c_reset();
				ms->last_exit_code_int = 0; 
			}
				
			close(fd);
		}
		// Check Outfile
		if (tmp_redir->type == TOKEN_REDIRECT)
		{
			fd = open(tmp_redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			printf("\t  open OUT file >%s< \n", tmp_redir->target);
			if (fd == -1)
			{
				c_red(); printf("\t\tError 1 --> TODO Error Handling Open OUT file in check_file \nCancel EXECUTION"); c_reset();
				ms->last_exit_code_int = 1; 			// richtiger Code?
			}
			else
			{
				c_green(); printf("\t\tFD: %i   --> TODO Error Handling Open file in check_file \n", fd); c_reset();
				ms->last_exit_code_int = 0; 
			}
				
			close(fd);
		}
		tmp_redir = tmp_redir->next;
	}
	
int		get_len_cmd(t_cmd *cmd)
{
	t_cmd	*tmp_cmd;
	int		count;

	tmp_cmd = cmd;
	count = 0;
	while (tmp_cmd)
	{
		tmp_cmd = tmp_cmd->next;
		count++;
	}
	
	return (count);
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