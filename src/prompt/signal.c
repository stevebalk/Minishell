/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:20:50 by jopeters          #+#    #+#             */
/*   Updated: 2023/12/19 18:15:43 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

void	handle_sigint(int sig)
{
    c_yellow(); printf("\nSig: %i \nControl-C pressed. Exiting.\n", sig);
    //exit(0);
}
