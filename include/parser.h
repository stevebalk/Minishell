/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:10:30 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/01 16:07:29 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/* struct to store the words and if it should get joined,
from lexer tokens */
// typedef struct	s_pword
// {
// 	char	*word;
// 	int		join;
// }

/* Redirection struct, used by t_cmd to save
redirections in a linked list*/
typedef struct	s_redir
{
	unsigned int	type;
	char			*target;
	struct s_redir	*next;
}				t_redir;

/* Parser struct, saves all redirections
and commands */
typedef struct	s_cmd
{
	char			**argv;
	t_redir			*redirs;
	struct s_cmd	*next;
}				t_cmd;

/* Parse struct, saves pointer to token list
and command list */
typedef struct	s_parse
{
	t_token	*tk;
	t_cmd	*cmd;
}				t_parse;

#endif