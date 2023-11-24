/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:09:04 by sbalk             #+#    #+#             */
/*   Updated: 2023/11/24 16:37:06 by sbalk            ###   ########.fr       */
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

size_t		is_quote(const char *str);
size_t		is_single_quote(const char *str);
size_t		is_double_quote(const char *str);
size_t		is_env_variable(const char *str);
size_t		is_exit_code_variable(const char *str);

#endif