/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_b.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 13:11:41 by jopeters          #+#    #+#             */
/*   Updated: 2023/12/04 13:12:03 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// copy the PATH splittet in array to ms struct
void	copy_path_to_ms_ms_struct(t_ms *ms)
{
	char 	*path_value;
	c_yellow(); printf("copy_path_to_ms_ms_struct()\n"); c_reset();

	path_value = get_val_of_var(&ms->env_llst, "PATH");
	ms->path_arr = ft_split(path_value, ':');

	if (path_value)
		free(path_value);
	c_red(); printf("~copy_path_to_ms_ms_struct()\n"); c_reset();
}

// copy the HOME dir of the env to ms struct
void	copy_env_home_to_ms_struct(t_ms *ms)
{
	char	*home_dir;

	c_yellow(); printf("copy_env_home_to_ms_struct()\n"); c_reset();
	home_dir = get_val_of_var(&ms->env_llst, "HOME");
	c_green();printf("home dir >%s<\n", home_dir); c_reset();
	ms->home_dir = join_three_string(home_dir, "", "");
	if (home_dir)
		free(home_dir);
	c_red(); printf("~copy_env_home_to_ms_struct()\n"); c_reset();
}