/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_b.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 13:11:41 by jopeters          #+#    #+#             */
/*   Updated: 2024/01/04 14:42:10 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// copy the PATH splittet in array to ms struct
void	copy_path_to_ms_struct(t_ms *ms)
{
	char	*path_value;

	path_value = get_val_of_var(&ms->env_llst, "PATH");
	ft_free_array((void **)ms->path_arr);
	if (path_value)
		ms->path_arr = ft_split(path_value, ':');
	free_n_null((void **)&path_value);
}

// copy the HOME dir of the env to ms struct
void	copy_env_home_to_ms_struct(t_ms *ms)
{
	char	*tmp_home_dir;

	tmp_home_dir = get_val_of_var(&ms->env_llst, "HOME");
	if (tmp_home_dir)
		ms->home_dir = join_three_string(tmp_home_dir, "", "");
	free_n_null((void **)&tmp_home_dir);
}

// exports a llst to char ** array; mallocs --> you have to free it!
char	**copy_llst_to_char_arr(t_list **llst, t_ms *ms)
{
	int		i;
	int		len;
	char	**arr;
	t_list	*tmp_llst;

	tmp_llst = *llst;
	len = ft_lstsize(*llst);
	arr = ft_calloc(len + 1, sizeof(char *));
	check_if_malloc_failed((void **)arr, ms);
	i = 0;
	while (tmp_llst)
	{
		arr[i] = ft_strdup((char *)tmp_llst->content);
		i++;
		tmp_llst = tmp_llst->next;
	}
	return (arr);
}
