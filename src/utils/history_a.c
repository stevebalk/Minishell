/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_a.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:10:02 by jopeters          #+#    #+#             */
/*   Updated: 2023/12/19 17:55:45 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtins.h"

void	history_master(t_ms *ms)
{
	load_history_llst(ms->tmp_history_folder_file, &ms->hist_llst);
	limit_history_llst(&ms->hist_llst);
	add_history_llst_to_prompt(&ms->hist_llst);
	write_history_llst(ms->tmp_history_folder_file, &ms->hist_llst);
}

void	add_history_llst_to_prompt(t_list **history_lst)
{
	t_list	*tmp_lst;

	tmp_lst = *history_lst;
	while (tmp_lst)
	{
		add_history((char *)tmp_lst->content);
		tmp_lst = tmp_lst->next;
	}
}

void	load_history_llst(char *hist_file_name, t_list **history_lst)
{
	char	*line;
	int		fd;

	fd = open(hist_file_name, O_RDONLY | O_CREAT, 0644);
	line = get_next_line(fd);
	while (line)
	{
		del_first_nl(line);
		if (!history_lst)
			*history_lst = ft_lstnew((void *)line);
		else
			ft_lstadd_back(history_lst, ft_lstnew((void *)line));
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	close(fd);
}

void	write_history_llst(char *hist_file_name, t_list **history_lst)
{
	t_list	*tmp_lst;
	int		fd;

	fd = open (hist_file_name, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	tmp_lst = *history_lst;
	while (tmp_lst)
	{
		if (find_newline((char *)tmp_lst->content) > -1
			&& (char *)tmp_lst->content)
			write(fd, (char *)tmp_lst->content,
				ft_strlen((char *)tmp_lst->content));
		else
		{
			write(fd, (char *)tmp_lst->content,
				ft_strlen((char *)tmp_lst->content));
			write(fd, "\n", 1);
		}
		tmp_lst = tmp_lst->next;
	}
	close (fd);
}
