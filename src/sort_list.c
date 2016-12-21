
#include "list.h"

t_list	*sort_list(t_list* lst, int (*cmp)(char* , char*))
{
	int		swap;
	t_list	*tmp;
	int	data_tmp;

	swap = 1;
	if (lst == 0)
		return (lst);
	while (swap)
	{
		swap = 0;
		tmp = lst;
		while (tmp->next)
		{
			if (cmp(tmp->content->name, tmp->next->content->name) < 0)
			{
				data_tmp = tmp->data;
				tmp->data = tmp->next->data;
				tmp->next->data = data_tmp;
				swap = 1;
			}
			tmp = tmp->next;
		}
	}
	return (tmp);
}
