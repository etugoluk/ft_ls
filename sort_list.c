/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etugoluk <etugoluk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 17:53:05 by etugoluk          #+#    #+#             */
/*   Updated: 2018/12/14 17:53:06 by etugoluk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	swap1(t_lst *l1, t_lst *l2)
{
	char		*name;
	char		*fullname;
	char		type;
	char		rights[11];
	long		links;
	char		*pw_name;

	name = l1->name;
	l1->name = l2->name;
	l2->name = name;
	fullname = l1->full_name;
	l1->full_name = l2->full_name;
	l2->full_name = fullname;
	type = l1->type;
	l1->type = l2->type;
	l2->type = type;
	ft_strncpy(rights, l1->rights, 11);
	ft_strncpy(l1->rights, l2->rights, 11);
	ft_strncpy(l2->rights, rights, 11);
	links = l1->links;
	l1->links = l2->links;
	l2->links = links;
	pw_name = l1->pw_name;
	l1->pw_name = l2->pw_name;
	l2->pw_name = pw_name;
}

void	swap2(t_lst *l1, t_lst *l2)
{
	char		*gr_name;
	long long	size;
	char		*time;
	time_t		mtime;
	char		*color;

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
	color = l1->color;
	l1->color = l2->color;
	l2->color = color;
}

void	sort_list(t_lst *list, int (*cmp)(t_lst *, t_lst *))
{
	t_lst	*tmp;

	tmp = list;
	while (list->next)
	{
		if (cmp(list, list->next) == 1)
		{
			swap1(list, list->next);
			swap2(list, list->next);
			list = tmp;
		}
		else
			list = list->next;
	}
	list = tmp;
}
