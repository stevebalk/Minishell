/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:10:30 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/18 21:08:23 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct	s_redir
{
	unsigned int	type;
	char			*param;
	struct s_redir	*next;
}				t_redir;

typedef struct	s_cmd
{
	char			**argv;
	t_redir			redirs;
	struct s_cmd	*next;
}				t_cmd;
