/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:10:02 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/13 14:50:17 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"



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
		/*
		add history linked list
		*/
        del_first_nl(line);
        if (!history_lst)
            *history_lst = ft_lstnew((void*)line);
        else
            ft_lstadd_back(history_lst, ft_lstnew((void*)line));
      
        //add_history(line);
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

int find_newline(char *str)
{
    int i;
    int nl;
    
    i = 0;
    nl = 0;
    
    while(str[i])
    {
        if (str[i] == '\n')
            nl = i;
        i++;
    }

    return (nl);
}

void del_first_nl(char *str)
{
    int nl_pos;
    nl_pos = find_newline(str);
    if (nl_pos > 0)
    {
        //printf("nl in in >%s<  pos: %i\n", str, nl_pos);
        str[nl_pos]= '\0';
    }
    //printf("after del_nl >%s<  \n", str);
} 

void write_history_llst(char *hist_file_name, t_list **history_lst)
{
	/*
		Todo:
		1. Truncate history file 
		2. Append every linked list line

        !!! if newline than no newline
	*/
    t_list *tmp_lst;
    int fd;
    
    fd = open(hist_file_name, O_WRONLY | O_TRUNC | O_CREAT, 0664);

    tmp_lst = *history_lst;
    
    while(tmp_lst)
    {
        printf("fd: %i   write >%s<   nl: %i\n", fd, (char*)tmp_lst->content, find_newline((char*)tmp_lst->content));
        
        if (find_newline((char*)tmp_lst->content) && (char*)tmp_lst->content)
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