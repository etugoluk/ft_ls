#include "ft_ls.h"

void	sort_list(t_lst	*list)
{
	char	*tmp_name;
	t_lst	*tmp;
	
	tmp = list;
	while (list->next)
	{
		if (ft_strcmp(list->name, list->next->name) > 0)
		{
			tmp_name = list->name;
			list->name = list->next->name;
			list->next->name = tmp_name;
			list = tmp;
		}
		else
			list = list->next;
	}
	list = tmp;
}
