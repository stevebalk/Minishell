/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_b.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 13:11:41 by jopeters          #+#    #+#             */
/*   Updated: 2023/12/21 18:30:20 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// copy the PATH splittet in array to ms struct
void	copy_path_to_ms_ms_struct(t_ms *ms)
{
	char 	*path_value;
	//c_yellow(); printf("copy_path_to_ms_ms_struct()\n"); c_reset();

	path_value = get_val_of_var(&ms->env_llst, "PATH");
	//printf("path value: >%s<\n", path_value);
	if (path_value)
		ms->path_arr = ft_split(path_value, ':');
	else
		ms->path_arr = ft_split("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin", ':');

	
	free_n_null((void **)&path_value);
	//c_red(); printf("~copy_path_to_ms_ms_struct()\n"); c_reset();
}

// copy the HOME dir of the env to ms struct
void	copy_env_home_to_ms_struct(t_ms *ms)
{
	char	*tmp_home_dir;

	//c_yellow(); printf("copy_env_home_to_ms_struct()\n"); c_reset();
	tmp_home_dir = get_val_of_var(&ms->env_llst, "HOME");
	//c_green();printf("home dir >%s<\n", tmp_home_dir); c_reset();
	ms->home_dir = join_three_string(tmp_home_dir, "", "");
	free_n_null((void **)&tmp_home_dir);
	//c_red(); printf("~copy_env_home_to_ms_struct()\n"); c_reset();
}

// exports a llst to char ** array; mallocs --> you have to free it!
char **copy_llst_to_char_arr(t_list **llst, t_ms *ms)
{
	int	i;
	int	len;
	char **arr;
	
	t_list *tmp_llst;
	tmp_llst = *llst;
	len = ft_lstsize(*llst);
	arr = ft_calloc(len + 1, sizeof(char *));
	// arr = (char **)malloc(sizeof(char *) * (len + 1));
	check_if_malloc_failed((void **)arr, ms);
	i = 0;
	
	while(tmp_llst)
	{
		//arr[i] = (char *)malloc(sizeof(char) * ft_strlen((char *)tmp_llst->content));
		arr[i] = ft_strdup((char *)tmp_llst->content);
		i++;
		tmp_llst = tmp_llst->next;
	}

	return (arr);	
}