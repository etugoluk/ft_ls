#include "ft_ls.h"

int		asc(t_lst *l1, t_lst *l2)
{
	return (ft_strcmp(l1->name, l2->name) >= 0) ? 1 : 0;
}

int		desc(t_lst *l1, t_lst *l2)
{
	return (ft_strcmp(l1->name, l2->name) <= 0) ? 1 : 0;
}

int		desc_time(t_lst *l1, t_lst *l2)
{
	return (l1->mtime > l2->mtime) ? 1 : 0;
}

void	swap(t_lst *l1, t_lst *l2)
{
	char		*name;
	char		type;
	char		rights[10];
	long		links;
	char		*pw_name;
	char		*gr_name;
	long long	size;
	char		*time;
	time_t		mtime;

	name = l1->name;
	l1->name = l2->name;
	l2->name = name;

	type = l1->type;
	l1->type = l2->type;
	l2->type = type;

	int i = 0;
	while (i < 10)
	{
		rights[i] = l1->rights[i];
		i++;
	}
	i = 0;
	while (i < 10)
	{
		l1->rights[i] = l2->rights[i];
		i++;
	}
	i = 0;
	while (i < 10)
	{
		l2->rights[i] = rights[i];
		i++;	
	}
	// rights = l1->rights;
	// l1->rights = l2->rights;
	// l2->rights = rights;

	links = l1->links;
	l1->links = l2->links;
	l2->links = links;

	pw_name = l1->pw_name;
	l1->pw_name = l2->pw_name;
	l2->pw_name = pw_name;

	gr_name = l1->gr_name;
	l1->gr_name = l2->gr_name;
	l2->gr_name = gr_name;

	size = l1->size;
	l1->size = l2->size;
	l2->size = size;

	time = l1->time;
	l1->time = l2->time;
	l2->time = time;

	mtime = l1->mtime;
	l1->mtime = l2->mtime;
	l2->mtime = mtime;

}

void	sort_list(t_lst *list, int (*cmp)(t_lst *, t_lst *))
{
	t_lst	*tmp;
	
	tmp = list;
	while (list->next)
	{
		if (cmp(list, list->next) == 0)
		{
			swap(list, list->next);
			list = tmp;
		}
		else
			list = list->next;
	}
	list = tmp;
}
