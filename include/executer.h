/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:55:28 by sbalk             #+#    #+#             */
/*   Updated: 2023/12/12 13:17:48 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

typedef enum	e_builtins
{
	BI_ECHO,
	BI_CD,
	BI_PWD,
	BI_EXPORT,
	BI_UNSET,
	BI_ENV,
	BI_EXIT
}				t_builtins;

#endif