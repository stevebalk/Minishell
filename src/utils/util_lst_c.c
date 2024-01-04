/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_lst_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:17:12 by jopeters          #+#    #+#             */
/*   Updated: 2024/01/04 16:34:14 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

// this function is for get_val_of_var();
// don´t call it alone!; its for finding the value of an var
void	get_val_of_var_v_alloc(char *v_name, void *cont, char **tmp_value)
{
	char		*tmp_str;
	t_var_names	tmp_var;
	int			l_v_name;
	int			l_cont;

	l_v_name = (int)ft_strlen(v_name);
	l_cont = (int)ft_strlen((char *)cont);
	tmp_str = (char *)malloc(sizeof(char) * (l_cont + 1));
	if (!tmp_str)
		return ;
	ft_strlcpy(tmp_str, (char *)cont, l_cont + 1);
	if ((ft_strncmp(v_name, (char *)cont, l_v_name) == 0)
		&& ((l_cont == l_v_name) || is_s_in_pos_of_str(tmp_str, l_v_name, '=')))
	{
		get_var_names(&tmp_var, tmp_str);
		if (tmp_var.value_without_quotes)
		{
			*tmp_value = (char *)malloc(sizeof(char)
					* (ft_strlen(tmp_var.value_without_quotes) + 1));
			if (!*tmp_value)
				return ;
			ft_strlcpy(*tmp_value, tmp_var.value_without_quotes,
				ft_strlen(tmp_var.value_without_quotes) + 1);
		}
		dealloc_var_names(&tmp_var);
	}
	free(tmp_str);
}

// returns the value of a variable; you have to free the mem;
// var_name without "="
char	*get_val_of_var(t_list **llst, char *var_name)
{
	t_list	*tmp_lst;
	char	*tmp_value;
	

	tmp_value = NULL;
	tmp_lst = *llst;
	while (tmp_lst)
	{
		get_val_of_var_v_alloc(var_name, tmp_lst->content, &tmp_value);
		tmp_lst = tmp_lst->next;
	}
	return (tmp_value);
}

