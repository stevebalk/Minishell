/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:08:20 by jopeters          #+#    #+#             */
/*   Updated: 2024/01/04 15:43:47 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtins.h"

void	show_history_llist(t_list **lst)
{
	int		i;
	t_list	*tmp_lst;

	tmp_lst = *lst;
	i = 0;
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

void	limit_history_llst(t_list **history_lst)
{
	while (ft_lstsize(*history_lst) > MAX_HISTORY)
		lst_delete_first(history_lst);
}

void	set_history_path(t_ms *ms)
{
	char	*path;
	char	*pwd;
	size_t	size;

	size = 1024;
	path = NULL;
	pwd = NULL;
	pwd = (char *)malloc(sizeof(char) * size);
	if (!pwd)
		return ;
	path = get_val_of_var(&ms->env_llst, "TMPDIR");
	if (path)
		ms->tmp_history_folder_file
			= join_three_string(path, "/", FILE_HISTORY);
	else
	{
		if (getcwd(pwd, size) == NULL) 
			perror("not get cwd for history after failed to set tmp dir\n");
		else
			ms->tmp_history_folder_file
				= join_three_string(pwd, "/", FILE_HISTORY);
	}
	free(path);
	free(pwd);
}
