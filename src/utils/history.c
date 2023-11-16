/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:10:02 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/16 14:47:33 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void history_master(t_list **history_lst)
{
    load_history_llst(FILE_HISTORY, history_lst);
    limit_history_llst(history_lst);
    add_history_llst_to_prompt(history_lst);
    write_history_llst(FILE_HISTORY, history_lst);
}

void add_history_llst_to_prompt(t_list **history_lst)
{
    t_list *tmp_lst;
    tmp_lst = *history_lst;

    while(tmp_lst)
    {
        add_history((char *)tmp_lst->content);
        tmp_lst = tmp_lst->next;
    }
}

void load_history_llst(char *hist_file_name, t_list **history_lst)
{
    char *line;
    int fd;
    fd = open(hist_file_name, O_RDONLY | O_CREAT, 0644);
    line = get_next_line(fd);

    while(line)
    {
        del_first_nl(line);
        if (!history_lst)
            *history_lst = ft_lstnew((void*)line);
        else
            ft_lstadd_back(history_lst, ft_lstnew((void*)line));
      
        line = get_next_line(fd);
    }
    
    if (line)
        free(line); 
    close(fd);
}

void show_history_llist(t_list **lst)
{
    int i;
    t_list *tmp_lst;
    tmp_lst = *lst;
    
    i = 0;
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

void limit_history_llst(t_list **history_lst)
{
    //t_list *tmp_lst;
    //tmp_lst = *history_lst;
	
    
    //c_yellow();printf("()limit_history\n");
    //printf("history length system: %i \n", ft_lstsize(*history_lst));
    //c_reset();
    //show_history_llist(history_lst);

    while(ft_lstsize(*history_lst) > MAX_HISTORY)
    {
        //c_red();printf("del first list > %s\n", (char*)(tmp_lst->content));c_reset();
        lst_delete_first(history_lst);
        //show_history_llist(history_lst);
    }
}

void write_history_llst(char *hist_file_name, t_list **history_lst)
{
    t_list *tmp_lst;
    int fd;
    
    fd = open(hist_file_name, O_WRONLY | O_TRUNC | O_CREAT, 0664);
    tmp_lst = *history_lst;
    
    while(tmp_lst)
    {
        //printf("fd: %i   write >%s<   nl: %i\n", fd, (char*)tmp_lst->content, find_newline((char*)tmp_lst->content));
        
        if (find_newline((char*)tmp_lst->content) > -1 && (char*)tmp_lst->content)
            write(fd, (char*)tmp_lst->content, ft_strlen((char*)tmp_lst->content));
        else
        {
            write(fd, (char*)tmp_lst->content, ft_strlen((char*)tmp_lst->content));
            write(fd, "\n", 1);
        }
        
        tmp_lst = tmp_lst->next;
    }
    close(fd);
}