/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etugoluk <etugoluk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 17:52:35 by etugoluk          #+#    #+#             */
/*   Updated: 2018/12/14 17:52:35 by etugoluk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	recursive(t_lst *files, t_ls *ls, char *dname)
{
	t_lst	*tmp;
	char	*tmpname;

	tmp = files;
	while (files)
	{
		if (files->type == 4 && ft_strcmp(files->name, ".") &&
			ft_strcmp(files->name, ".."))
		{
			if (files->name[0] == '.' && !ls->a_flag)
			{
				files = files->next;
				continue;
			}
			tmpname = full_name(dname, files->name);
			new_dir(tmpname, ls);
			free(tmpname);
		}
		files = files->next;
	}
	files = tmp;
}

t_dir	*set_dir(t_ls *ls, char *str)
{
	t_dir *d;

	d = (t_dir *)malloc(sizeof(t_dir));
	if (!(d->dir_name = opendir(str)))
	{
		ft_printf("ft_ls: %s: %s\n", str, strerror(errno));
		free(d);
		d = NULL;
		return (d);
	}
	d->str_name = ft_strdup(str);
	get_files(d, ls);
	d->next = NULL;
	return (d);
}

void	new_dir(char *str, t_ls *ls)
{
	struct s_dir *tmp;

	if (!ls->d)
	{
		if (!(ls->d = set_dir(ls, str)))
			return ;
		if (ls->R_flag)
			recursive(ls->d->files, ls, ls->d->str_name);
		closedir(ls->d->dir_name);
		return ;
	}
	tmp = ls->d;
	while (ls->d->next)
		ls->d = ls->d->next;
	if (!(ls->d->next = set_dir(ls, str)))
		return ;
	if (ls->R_flag)
		recursive(ls->d->next->files, ls, ls->d->next->str_name);
	closedir(ls->d->next->dir_name);
	ls->d = tmp;
}
