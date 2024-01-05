/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_b.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 13:11:41 by jopeters          #+#    #+#             */
/*   Updated: 2024/01/05 11:41:04 by sbalk            ###   ########.fr       */
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
	else
		ms->path_arr = NULL;
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

// adds +1 to the SHLVL env/export variable
void	add_shell_level(t_list **env_llst, t_list **env_llst_sorted)
{
	char		*tmp_var_with_value;
	char		*tmp_value;
	char		*new_value;
	t_var_names	var;

	tmp_value = get_val_of_var(env_llst, "SHLVL");
	if (tmp_value)
	{
		var.self_value = ft_atoi(tmp_value) + 1;
		new_value = ft_itoa(var.self_value);
		tmp_var_with_value = join_three_string("SHLVL", "=", new_value);
	}
	else
	{
		new_value = ft_itoa(0);
		tmp_var_with_value = join_three_string("SHLVL", "=", new_value);
	}
	get_var_names(&var, tmp_var_with_value);
	update_or_create_llst_var(env_llst, env_llst_sorted, &var);
	free_n_null((void **)&new_value);
	free_n_null((void **)&tmp_var_with_value);
	free_n_null((void **)&tmp_value);
	dealloc_var_names(&var);
}

// update the "SHELL" variable with PWD
void	set_shell_var_to_pwd(t_list **env_llst, t_list **env_llst_sorted)
{
	char	*shell;
	char	*buffer;
	size_t	size;

	size = 1024;
	buffer = (char *)ft_calloc(size, sizeof(char));
	getcwd(buffer, size);
	shell = join_three_string("SHELL=", buffer, "/minishell");
	export_single_arg(env_llst, env_llst_sorted, shell);
	free(shell);
	free(buffer);
}
