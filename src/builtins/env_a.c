/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_a.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:22:48 by jopeters          #+#    #+#             */
/*   Updated: 2024/01/05 19:56:19 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

// shows all entries of the env array coming from outside by argument 3
void	show_env_arr(char **env)
{
	int	i;

	i = -1;
	while (i++, env[i])
		printf("i: %i  >%s<\n", i, env[i]);
}

// copy the env array to a new llist
void	load_env_to_llst(t_list **env_lst, char **env)
{
	char	*str;
	int		i;

	i = -1;
	if (!env[0])
	{
		str = (char *)ft_calloc(1, sizeof(char));
		ft_lstadd_back(env_lst, ft_lstnew((void *)str));
	}
	else
	{
		while (i++, env[i] && ft_strlen(env[i]) > 0)
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
}

// showing all list entrys seperated by a newline
int	show_env_llist(t_list **lst)
{
	int		exit_code;
	t_list	*tmp_lst;

	exit_code = 0;
	tmp_lst = *lst;
	while (tmp_lst)
	{
		if (ft_strlen((char *)tmp_lst->content) > 0)
			printf("%s\n", (char *)tmp_lst->content);
		tmp_lst = tmp_lst->next;
	}
	return (exit_code);
}

void	show_export_llist_line(char *line)
{
	int	ichar;

	ichar = -1;
	printf("declare -x ");
	while (ichar++, line[ichar])
	{
		printf("%c", line[ichar]);
		if (line[ichar] == '=')
		{
			if (line[ichar + 1] != '\"' && line[ichar + 1] != '\0')
				printf("\"");
		}
	}
	if (line[ichar - 1] != '\"')
		printf("\"");
	printf("\n");
}

int	show_export_llist(t_list **lst)
{
	t_list	*tmp_lst;
	char	*line;

	tmp_lst = *lst;
	while (tmp_lst)
	{
		line = (char *)tmp_lst->content;
		if (ft_strlen(line) > 0)
			show_export_llist_line(line);
		tmp_lst = tmp_lst->next;
	}
	return (0);
}
