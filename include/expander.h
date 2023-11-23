/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:09:04 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/22 18:10:57 by sbalk            ###   ########.fr       */
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

void	check_valid_quote_count(t_token *token, t_ms *ms);

#endif