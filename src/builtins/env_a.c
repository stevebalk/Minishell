/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_a.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:22:48 by jopeters          #+#    #+#             */
/*   Updated: 2024/01/03 12:57:37 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"


// adding a node with a string to a linked list i.a "A=hello"; no parsing involved!; creates a new llist if llist is null; mallocs for char *
void	add_variable_to_llst(t_list **llst, char *var)
{
	char	*str;
	//c_yellow(); printf("add_variable_to_llst() var >%s<\n", var); c_reset();
	
	str = (char *)malloc(sizeof(char) * (ft_strlen(var) + 1));
	ft_strlcpy(str, var, ft_strlen(var) + 1);
	if (!llst)
		*llst = ft_lstnew((void *)str);
	else
		ft_lstadd_back(llst, ft_lstnew((void *)str));
}

// shows all entries of the env array coming from outside by argument 3
void	show_env_arr(char **env)
{
	int	i;
	//c_yellow(); printf("show_env_arr()\n"); c_reset();

	i = -1;
	while (i++, env[i])
		printf("i: %i  >%s<\n", i, env[i]);
}

// copy the env array to a new llist
void	load_env_to_llst(t_list **env_lst, char **env)
{
	char	*str;
	int		i;
	//c_yellow(); printf("load_env()\n"); c_reset();
	//show_env_arr(env);
	i = -1;
	if (!env[0])
	{
		//printf("!env[0]\n");
		str = (char*)ft_calloc(1, sizeof(char));
		ft_lstadd_back(env_lst, ft_lstnew((void *)str));
	}
	else
	{
		while (i++, env[i] && ft_strlen(env[i])> 0)
		{
			str = (char *)malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
			if (!str)
				return ;
			ft_strlcpy(str, env[i], ft_strlen(env[i]) + 1);
			if (!env_lst)
				*env_lst = ft_lstnew((void *)str);
			else
				ft_lstadd_back(env_lst, ft_lstnew((void *)str));
		}
	}
	//c_yellow(); printf("~load_env()\n"); c_reset();
}

// showing all list entrys seperated by a newline
int	show_env_llist(t_list **lst)
{
	int		exit_code;
	t_list	*tmp_lst;

	exit_code = 0;
	tmp_lst = *lst;
	//c_yellow(); printf("show_env_llist()\n"); c_reset();
	while (tmp_lst)
	{
		c_green();
		if (ft_strlen((char *)tmp_lst->content) > 0)
			printf("%s\n", (char *)tmp_lst->content);
		c_reset();
		tmp_lst = tmp_lst->next;
	}

	return (exit_code);
}

int	show_export_llist(t_list **lst)
{
	int		ichar;
	t_list	*tmp_lst;
	char	*line;

	tmp_lst = *lst;
	while (tmp_lst)
	{
		line = (char *)tmp_lst->content;
		if (ft_strlen(line) > 0)
		{
			c_reset();
			printf("declare -x ");
			c_green();
			ichar = 0;
			while( line[ichar])	
			{
				printf("%c", line[ichar]);
				if (line[ichar] == '=')	
				{
					if (line[ichar+1] != '\"' && line[ichar+1] != '\0')
						printf("\"");
				}
				ichar++;
			}
			if (line[ichar-1] != '\"')
				printf("\"");
			c_reset();
			printf("\n");
		}
		tmp_lst = tmp_lst->next;
	}
	return (0);
}

// adds +1 to the SHLVL env/export variable
void add_shell_level(t_list **env_llst, t_list **env_llst_sorted)
{
	/* 
	1. reading the val of SHLVL
	2. converting into int                      
	3. +1
	4. converting into string
	5. updating ENV/Export              
	
	*/
	//c_yellow(); printf("add_shell_level()\n"); c_reset();

	char		*tmp_var_with_value;
	char		*tmp_value;
	char		*new_value;
	t_var_names	var;
	
	//show_env_llist(env_llst);

	tmp_value = get_val_of_var(env_llst, "SHLVL");
	
	if (tmp_value)
	{
		var.self_value = ft_atoi(tmp_value) + 1;
		new_value =  ft_itoa(var.self_value);
		tmp_var_with_value = join_three_string("SHLVL", "=", new_value);
	}
	else
	{
		new_value =  ft_itoa(0);
		tmp_var_with_value = join_three_string("SHLVL", "=", new_value);
	}

	get_var_names(&var, tmp_var_with_value);
	update_or_create_llst_var(env_llst, env_llst_sorted, &var);
	
	free_n_null((void **)&new_value);
	free_n_null((void **)&tmp_var_with_value);
	free_n_null((void **)&tmp_value);
	dealloc_var_names(&var);

	//c_red(); printf("~add_shell_level()\n"); c_reset();
}

// update the "SHELL" variable with PWD
void	set_shell_var_to_pwd(t_list **env_llst, t_list **env_llst_sorted)
{
	char	*pwd;
	char	*shell;
	char	*buffer;
	size_t	size;

	size = 1024;
	buffer = (char *)ft_calloc(size, sizeof(char));
	 
	//printf("set_shell_var_to_pwd  file: %s   line: %d\n", __FILE__, __LINE__);
	pwd = get_val_of_var(env_llst, "PWD");
	//printf("xxx pwd: %s\n", pwd);
	if (!pwd)
	{
		getcwd(buffer, size);
		shell = join_three_string("SHELL=", buffer, "");

	}
	else
		shell = join_three_string("SHELL=", pwd, "");

	//printf("xxx pwd: %s\n", pwd);

	//shell = join_three_string("SHELL=", pwd, "");
	//printf("shell: >%s<\n", shell);
	export_single_arg(env_llst, env_llst_sorted, shell);
	free(shell);
	free(buffer);
	free(pwd);
}

	

/*
Achtung:
bei Export wird alles in "" gespeichert, auch wenn es als a='huhu' reinkommt
bei Env wird es ohne "" gespeichert es sei denn es gehört dazu a='"huhu"'

*/