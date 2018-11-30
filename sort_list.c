#include "ft_ls.h"

int		asc(char *a, char *b)
{
	return (ft_strcmp(a, b) >= 0) ? 1 : 0;
}

int		desc(char *a, char *b)
{
	return (ft_strcmp(a, b) <= 0) ? 1 : 0;
}

void	sort_list(t_lst	*list, int (*cmp)(char*, char*))
{
	char	*tmp_name;
	char	tmp_type;
	t_lst	*tmp;
	
	tmp = list;
	while (list->next)
	{
		if (cmp(list->name, list->next->name) == 0)
		{
			tmp_name = list->name;
			tmp_type = list->type;
			list->name = list->next->name;
			list->type = list->next->type;
			list->next->name = tmp_name;
			list->next->type = tmp_type;
			list = tmp;
		}
		else
			list = list->next;
	}
	list = tmp;
}
