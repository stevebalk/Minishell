/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:08:20 by jopeters          #+#    #+#             */
/*   Updated: 2023/12/19 17:16:46 by jopeters         ###   ########.fr       */
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

void set_history_path(t_ms *ms)
{
	char *path;
	char *pwd;
    size_t size = 1024;
	
	(void)ms;
	path = NULL;
	pwd = NULL;
	
	//c_yellow(); printf("set_history_path\n");
	//c_reset();
	
	pwd = (char *)malloc(sizeof(char) * size);
	if (!pwd)
		return ;
	path = get_val_of_var(&ms->env_llst, "TMPDIR");
	if (path)
		ms->tmp_history_folder_file = join_three_string(path, "/", FILE_HISTORY);
	else
	{
		if (getcwd(pwd, size) == NULL) 
			perror("couldn´t get cwd for history after failed to set tmp directory\n");
		else
			ms->tmp_history_folder_file = join_three_string(pwd, "/", FILE_HISTORY);
	}
	//printf(">>%s<<     pwd >>%s<<    path >>%s<<\n", ms->tmp_history_folder_file, pwd, path);
	//printf("ms->tmp_his_folder_file >>%s<<  \n", ms->tmp_history_folder_file);

	//show_env_arr(env);

	free(path);
	free(pwd);
}