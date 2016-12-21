/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahunt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 00:57:35 by ahunt             #+#    #+#             */
/*   Updated: 2016/10/11 00:57:52 by ahunt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	print_list(t_list *list)
{
	t_list	*link;
	t_tet	*temp;
	int		i;

	link = list;
	while (link != NULL)
	{
		temp = (t_tet *)(link->content);
		i = 0;
		while (i < temp->height)
		{
			ft_putendl(temp->tab[i]);
			i++;
		}
		link = link->next;
	}
}

t_list	*ft_lstrev(t_list **list)
{
	t_list	*next;
	t_list	*current;
	t_list	*prev;

	prev = NULL;
	current = *list;
	while (current)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*list = prev;
	return (*list);
}

int		ft_lstcount(t_list *list)
{
	if (list->next == NULL)
		return (1);
	return (1 + ft_lstcount(list->next));
}

t_list	*free_list(t_list *list)
{
	t_tet	*tetri;
	t_list	*next;

	while (list)
	{
		tetri = (t_tet *)(list->content);
		free_tetri(tetri);
		next = list->next;
		ft_memdel((void **)&list);
		list = next;
	}
	return (NULL);
}
