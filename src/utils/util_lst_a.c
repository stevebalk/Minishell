/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_lst_a.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:35:14 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/23 16:26:56 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

// delete fir node of a linked list
void	lst_delete_first(t_list **llist)
{
	t_list	*temp;

	if (*llist == NULL)
		return ;

	temp = *llist;
	*llist = (*llist)->next;
	free(temp->content);
	free(temp);
}

// free llist and optional the content
void	lst_dealloc(t_list **llist, int free_content)
{
	t_list	*cur;
	t_list	*aux;

	cur = *llist;
	while (cur != NULL)
	{
		aux = cur;
		cur = cur->next;
		if (aux->content && free_content)
			free(aux->content);
		free(aux);
	}
	*llist = NULL;
}

// updates the content of a node 
void	update_content_in_node(t_list *node, char *new_content)
{
	c_yellow(); printf("update_content_in_node() --> new_content >%s<   old node->content >%s<\n", new_content, (char*)node->content); c_reset();

	if (node && node->content)
		free(node->content);
	else
		return ;
	node->content = (char *)malloc(sizeof(char) * (ft_strlen(new_content) + 1));
	ft_strlcpy(node->content, new_content, ft_strlen(new_content) + 1);
}

// finds var in llst and returns the node
t_list	*find_var_in_llst(t_list **llst, char *var)
{
	t_list	*tmp_lst;
	char	*tmp_str;

	tmp_lst = *llst;
	c_yellow(); printf("find_var_in_llst() --> var >%s<\n", var); c_reset();
	while (tmp_lst)
	{
		tmp_str = (char*)tmp_lst->content;
		if ((ft_strncmp(var, (char*)tmp_lst->content, ft_strlen(var)) == 0) && ((ft_strlen(tmp_str) == ft_strlen(var)) || (tmp_str[ft_strlen(var)] == '=')))
		{
			c_green(); printf("  -> found var >%s< with = \n", var);
			c_purple(); printf("  -> content >%s< \n", tmp_str);
			return (tmp_lst);
			break ;
		}
		tmp_lst = tmp_lst->next;
	}
	c_red(); printf("~find_var_in_llst() --> not found >%s<\n", var); c_reset();
	return (NULL);
}

char *get_val_of_var(t_list **llst, char *var_name)
{
	t_list	*tmp_lst;
	char	*tmp_str;
	char	*tmp_value;
	t_var_names tmp_var;

	tmp_lst = *llst;
	c_yellow(); printf("get_val_of_var() --> var_name >%s<\n", var_name); c_reset();
	while (tmp_lst)
	{
		tmp_str = (char*)tmp_lst->content;
		if ((ft_strncmp(var_name, (char*)tmp_lst->content, ft_strlen(var_name)) == 0) && ((ft_strlen(tmp_str) == ft_strlen(var_name)) || (tmp_str[ft_strlen(var_name)] == '=')))
		{
			get_var_names(&tmp_var, tmp_str);
			c_green(); printf("  -> found var >%s< with \n", var_name);
			c_purple(); printf("  -> Value >%s< \n", tmp_var.value_without_quotes);
		
			tmp_value = (char *)malloc(sizeof(char) * ft_strlen(tmp_var.value_without_quotes));

			ft_strlcpy(tmp_value, tmp_var.value_without_quotes, ft_strlen(tmp_var.value_without_quotes) +1);
			dealloc_var_names(&tmp_var);
			//free(tmp_str);
			if (!tmp_value)
				return (NULL);
			c_red(); printf("~get_val_of_var() --> var_name>%s<   value >%s<\n", var_name, tmp_value); c_reset();

			return (tmp_value);
			break ;
		}
		tmp_lst = tmp_lst->next;
	}
	
	c_red(); printf("~get_val_of_var() --> var_name>%s<   value >%s<\n", var_name, tmp_str); c_reset();
	return (NULL);
}