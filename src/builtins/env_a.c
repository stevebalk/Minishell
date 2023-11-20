/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_a.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:22:48 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/20 11:02:47 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

// shows sorted env list when typing "export", 
void	test_parser_export(t_list **env_llst, t_list **env_llst_sorted, char *str)
{
	char	*clean_var_no_equal;
	char	*tmp_string_no_quotes;
	if (ft_strncmp("export", str, 6) == 0 && ft_strlen(str) == 6) // Export  || sort and show list
	{
		sort_list(*env_llst_sorted);
		show_env_llist(env_llst_sorted);
	}
	else if (ft_strncmp("export", str, 6) == 0 && ft_strlen(str) > 6) // Export A="huhu" || adds variable to list
	{
		c_cyan(); printf("test_parser_export  add variable  >%s<   len: %i \n", str, (int)ft_strlen(str)); c_reset();
		clean_var_no_equal = get_string_till_first_symbol(str+7, '=');
		tmp_string_no_quotes = get_string_without_symbols(str+7, '"');
		printf(" --> clean var name >%s<\n", clean_var_no_equal);
		// Check if variable is there if not add variable
		if (find_var_in_llst(env_llst, clean_var_no_equal))
		{
			update_content_in_node(find_var_in_llst(env_llst, clean_var_no_equal), str + 7);
			update_content_in_node(find_var_in_llst(env_llst_sorted, clean_var_no_equal), tmp_string_no_quotes);
		}
		else
		{
			add_variable_to_llst(env_llst, str + 7);
			add_variable_to_llst(env_llst_sorted, tmp_string_no_quotes);
		}

		free(clean_var_no_equal);
		free(tmp_string_no_quotes);
	}
	else if (ft_strncmp("env", str, 3) == 0 && ft_strlen(str) == 3)	// shows env list
		show_env_llist(env_llst);
}

// adding a node with a string to a linked list i.a "A=hello"; no parsing involved!; creates a new llist if llist is null; mallocs for char *
void	add_variable_to_llst(t_list **llst, char *var)
{
	c_yellow(); printf("add_variable_to_llst() var >%s<\n", var); c_reset();
	char	*str;
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
	c_yellow(); printf("show_env_arr()\n"); c_reset();
	int	i;

	i = -1;
	while (i++, env[i])
		printf("i: %i  >%s<\n", i, env[i]);
}

// copy the env array to a new llist
void	load_env_to_llst(t_list **env_lst, char **env)
{
	c_yellow(); printf("load_env()\n"); c_reset();
	char	*str;
	int		i;

	i = -1;
	while (i++, env[i])
	{
		str = (char *)malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
		ft_strlcpy(str, env[i], ft_strlen(env[i]) + 1);
		if (!env_lst)
			*env_lst = ft_lstnew((void *)str);
		else
			ft_lstadd_back(env_lst, ft_lstnew((void *)str));
	}
	c_yellow(); printf("~load_env()\n"); c_reset();
}

// showing all list entrys seperated by a newline
void	show_env_llist(t_list **lst)
{
	int		i;
	t_list	*tmp_lst;

	tmp_lst = *lst;
	i = 0;

	c_yellow(); printf("show_env_llist()\n"); c_reset();
	while (tmp_lst)
	{
		printf("i: %i  >", i);
		c_green();
		printf("%s", (char *)tmp_lst->content);
		c_reset();
		printf("<\n");
		tmp_lst = tmp_lst->next;
		i++;
	}
}



/*
Achtung:
bei Export wird alles in "" gespeichert, auch wenn es als a='huhu' reinkommt
bei Env wird es ohne "" gespeichert es sei denn es gehört dazu a='"huhu"'


*/