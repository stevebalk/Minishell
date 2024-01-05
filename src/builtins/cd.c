/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:05:04 by jopeters          #+#    #+#             */
/*   Updated: 2024/01/05 17:35:00 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/minishell.h"

static void	builtin_cd_if_home(t_ms *ms, int *exit_code)
{
	char	*tmp_str;

	tmp_str = get_val_of_var(&ms->env_llst, "HOME");
	if (tmp_str)
		*exit_code = builtin_cd_change_dir(&ms->env_llst,
				&ms->env_llst_sorted, tmp_str);
	else
	{
		perror("cd: HOME not set\n");
		*exit_code = 1;
	}
	free_n_null((void **)&tmp_str);
}

static void	builtin_cd_if_lastdir(t_ms *ms, int *exit_code)
{
	char	*tmp_str;

	tmp_str = get_val_of_var(&ms->env_llst, "OLDPWD");
	if (!tmp_str)
	{
		c_red();
		fflush(stdout);
		write(STDERR_FILENO, "minishell: cd: OLDPWD not set\n", 30);
		c_reset();
		*exit_code = 1;
	}
	else
	{
		*exit_code = builtin_cd_change_dir(&ms->env_llst,
				&ms->env_llst_sorted, tmp_str);
		builtin_pwd(&ms->env_llst, &ms->env_llst_sorted, 1);
		free_n_null((void **)&tmp_str);
	}
}

// executes cd - cd ~  and other cd 
int	builtin_cd(t_ms *ms, char **argv)
{
	int		exit_code;
	char	*in;

	exit_code = 0;
	if (get_size_of_array(argv) > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	in = argv[1];
	if ((!in) || (ft_strncmp(in, "", 0) == 0 && ft_strlen(in) == 0))
		builtin_cd_if_home(ms, &exit_code);
	else if (ft_strncmp(in, "-", 1) == 0 && ft_strlen(in) == 1)
		builtin_cd_if_lastdir(ms, &exit_code);
	else if (ft_strncmp(in, "~", 1) == 0 && ft_strlen(in) == 1)
		exit_code = builtin_cd_change_dir(&ms->env_llst,
				&ms->env_llst_sorted, ms->home_dir);
	else
		exit_code = builtin_cd_change_dir(&ms->env_llst,
				&ms->env_llst_sorted, in);
	return (exit_code);
}

// handles pwd after chdir
static int	builtin_cd_chge_dir_pwd(t_list **env_llst,
		t_list **env_llst_sorted, char *path, int exit_code)
{
	char	*tmp_value;
	char	*last_pwd;

	last_pwd = get_val_of_var(env_llst, "PWD");
	if (exit_code != 0)
	{
		c_red();
		fflush(stdout);
		ft_putstr_fd("minishell", 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		free_n_null((void **)&last_pwd);
		exit_code = 1;
	}
	else
	{
		tmp_value = join_three_string("OLDPWD", "=", last_pwd);
		export_single_arg(env_llst, env_llst_sorted, tmp_value);
		builtin_pwd(env_llst, env_llst_sorted, 0);
		free(tmp_value);
	}
	free_n_null((void **)&last_pwd);
	return (exit_code);
}

int	builtin_cd_change_dir(t_list **env_llst,
		t_list **env_llst_sorted, char *path)
{
	int		exit_code;

	exit_code = 0;
	if (!path)
		return (exit_code = 1, exit_code);
	exit_code = chdir(path);
	exit_code = builtin_cd_chge_dir_pwd(env_llst,
			env_llst_sorted, path, exit_code);
	return (exit_code);
}
