/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_a.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:22:48 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/14 14:24:52 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void show_env_arr(char **env)
{
	c_yellow(); printf("show_env_arr()\n"); c_reset();

	int i;
	i = -1;
	while(i++, env[i])
		printf("i: %i  >%s<\n", i, env[i]);
}

void load_env_to_llst(t_list **env_lst, char **env)
{
	c_yellow(); printf("load_env()\n"); c_reset();

	(void)env_lst;
	(void)env;

	int i;
	i = -1;
	while(i++, env[i])
	{
		//printf("i: %i  >%s<\n", i, env[i]);
        if (!env_lst)
            *env_lst = ft_lstnew((void*)env[i]);
        else
            ft_lstadd_back(env_lst, ft_lstnew((void*)env[i]));
	}
	c_yellow(); printf("~load_env()\n"); c_reset();
}

void show_env_llist(t_list **lst)
{
    int i;
    t_list *tmp_lst;
    tmp_lst = *lst;
    
    i = 0;
	c_yellow(); printf("show_env_llist()\n"); c_reset();
    while(tmp_lst)
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

void print_alphabetical(t_list **lst)
{
	char c;
	c_yellow(); printf("print_alphabetical()\n"); c_reset();

	c = 65;
	while (c < 123)
	{
		if (c == 91)
			c = 95;
		if (c == 96)
			c = 97;
		if (get_alphabetical_entry(lst, c))
			printf("%s\n", get_alphabetical_entry(lst, c));

		c++;
	}
	
	c_yellow(); printf("~print_alphabetical()\n"); c_reset();
}


char *get_alphabetical_entry(t_list **lst, char c)
{
	int i;	
	int j;
	char *str;
	t_list *tmp_lst;
    tmp_lst = *lst;

	i = 0;
	j = 0;

	/*
	1. start c mit A
	2. die liste durchgen ob es A gibt
		a. wenn ja, dann schauen ob es noch einen mit A gibt
		-> nein -> fertig
		-> ja -> 
	*/
	//c = 65;
    while(tmp_lst)
    {
		str = (char*)(tmp_lst->content);
		if (c == str[i])
		{
			return (char*)(tmp_lst->content);
		}

		tmp_lst = tmp_lst->next;
	}
	
	return NULL;
}


/*
Sortion

A = 65
B
Z = 90
- = 95
_A
__
a = 97
b
z = 122



*/

