/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_lst_a.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:35:14 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/13 10:36:02 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
t_list	*ft_lstnew(int content)
{
	t_list	*tmp;

	tmp = NULL;
	tmp = (t_list *) malloc (sizeof(t_list));
	if (tmp == NULL)
		return (0);
	tmp->content = content;
	tmp->next = NULL;
	return (tmp);
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (lst)
	{
		if (!*lst)
			*lst = new;
		else
		{
			current = ft_lstlast(*(lst));
			current->next = new;
		}
	}
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	tmp = *lst;
	if (lst != NULL)
	{
		while (tmp)
		{
			tmp = tmp->next;
			ft_lstdelone(*lst, del);
			(*lst) = tmp;
		}
	}
}
*/