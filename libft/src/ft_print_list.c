/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahunt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 20:57:02 by ahunt             #+#    #+#             */
/*   Updated: 2016/12/20 20:57:16 by ahunt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_list(t_list *list)
{
	t_list	*link;
	char 	*temp;
	int		i;

	link = list;
	while (link != NULL)
	{
		temp = (link->content);
		i = 0;
		while (temp[i])
		{
			ft_putendl(temp);
			i++;
		}
		link = link->next;
	}
}
