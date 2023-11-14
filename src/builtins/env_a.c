/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_a.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:22:48 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/14 16:49:21 by jopeters         ###   ########.fr       */
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
	char *str;

	int i;
	i = -1;
	while(i++, env[i])
	{
		str = (char *)malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
		ft_strlcpy(str, env[i], ft_strlen(env[i]) + 1);
		//printf("i: %i  >%s<\n", i, env[i]);
        if (!env_lst)
			*env_lst = ft_lstnew((void*)str);
        else
            ft_lstadd_back(env_lst, ft_lstnew((void*)str));
		
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
