/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:10:30 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/05 13:18:05 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/* Redirection struct, used by t_cmd to save
redirections in a linked list*/
typedef struct s_redir
{
	unsigned int	type;
	char			*target;
	struct s_redir	*next;
}				t_redir;

/* Parser struct, saves all redirections
and commands */
typedef struct s_cmd
{
	char			**argv;
	t_redir			*redirs;
	struct s_cmd	*next;
}				t_cmd;

#endif