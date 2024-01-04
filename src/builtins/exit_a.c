/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:43:55 by jopeters          #+#    #+#             */
/*   Updated: 2024/01/04 15:03:06 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/minishell.h"

void	exit_handler(t_ms *ms)
{
	c_red();
	write(STDERR_FILENO, "exit\n", 5);
	c_cyan();
	c_reset();
	free_ms(ms);
	exit(0);
}
