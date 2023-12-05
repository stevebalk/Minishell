/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:31:29 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/05 15:03:56 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Checks if malloc failed and if so ends the shell */
void	check_if_malloc_failed(void *src, t_ms *ms)
{
	if (src == NULL)
		ms_error(ms, NULL, 1, 1);
}
