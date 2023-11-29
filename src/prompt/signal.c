/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:20:50 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/29 13:30:04 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

void	handle_sigint(int sig)
{
    c_yellow(); printf("\nSig: %i \nControl-C pressed. Exiting.\n", sig);
    //exit(0);
}
