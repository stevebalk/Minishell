/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:09:04 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/23 16:49:43 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

#define QUOTE "\'\""

typedef struct	s_expand
{
	char			*str;
	struct s_expand	*next;
}				t_expand;

void		check_valid_quote_count(t_token *token, t_ms *ms);
int			is_quote(char *str);
int			is_single_quote(char *str);
int			is_double_quote(char *str);
int			is_variable(char *str);

t_expand	*create_expand_node(t_ms *ms);
t_expand	*append_chunk(t_ms *ms);

void	expand_varible(char **str, t_ms *ms, char *quote);


#endif