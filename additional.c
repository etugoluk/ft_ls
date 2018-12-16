/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etugoluk <etugoluk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 19:30:05 by etugoluk          #+#    #+#             */
/*   Updated: 2018/12/14 19:30:09 by etugoluk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		asc(t_lst *l1, t_lst *l2)
{
	return (ft_strcmp(l1->name, l2->name) <= 0) ? 1 : 0;
}

int		desc(t_lst *l1, t_lst *l2)
{
	return (ft_strcmp(l1->name, l2->name) >= 0) ? 1 : 0;
}

int		desc_time(t_lst *l1, t_lst *l2)
{
	return (l1->mtime < l2->mtime ||
		(l1->mtime == l2->mtime && ft_strcmp(l1->name, l2->name) <= 0)) ? 1 : 0;
}

void	clear_dir(t_dir *d)
{
	free(d->str_name);
	while (d->files)
	{
		free(d->files->name);
		free(d->files->pw_name);
		free(d->files->gr_name);
		free(d->files->time);
		free(d->files);
		d->files = d->files->next;
	}
	// free(d);
}
