/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etugoluk <etugoluk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 17:52:58 by etugoluk          #+#    #+#             */
/*   Updated: 2018/12/14 17:52:58 by etugoluk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_long(t_lst *f, t_dir *d, t_ls *ls)
{
	char	linkname[256];

	if (f->type == DT_BLK)
		ft_putchar('b');
	else if (f->type == DT_CHR)
		ft_putchar('c');
	else if (f->type == DT_DIR)
		ft_putchar('d');
	else if (f->type == DT_FIFO)
		ft_putchar('p');
	else if (f->type == DT_LNK)
		ft_putchar('l');
	else if (f->type == DT_REG)
		ft_putchar('-');
	else if (f->type == DT_SOCK)
		ft_putchar('s');
	ft_printf("%-11s%*ld %-*s  %-*s%*lld %s ", f->rights, d->link_max, f->links,
		d->pw_max, f->pw_name, d->gr_max, f->gr_name, d->digits_max + 2, f->size, f->time);
	if (ls->G_flag)
		ft_printf("\033%s%s\033[0m", f->color, f->name);
	else
		ft_printf("%s", f->name);
	if (f->type == DT_LNK)
	{
		readlink(f->full_name, linkname, 256);
		ft_printf(" -> %s", linkname);
	}
	ft_putchar('\n');
}

void	print_info(t_ls *ls, t_lst *f, t_dir *d, int *k)
{
	if ((ls->dir_flag && f->type != DT_DIR) ||
		(ls->reg_flag && f->type != DT_REG) ||
		(ls->link_flag && f->type != DT_LNK))
		return ;
	if (f->name[0] != '.' || (ls->a_flag))
	{
		if (ls->l_flag)
			print_long(f, d, ls);
		else
		{
			if (ls->G_flag)
				ft_printf("\033%s", f->color);
			if ((!ls->col_flag) ||
				((ls->col_flag) && (*k % ls->col_flag == ls->col_flag - 1)))
				ft_printf("%s\n", f->name);
			else if (ls->col_flag)
				ft_printf("%-*s", f->color, d->name_max + 8, f->name);
			if (ls->G_flag)
				ft_printf("\033[0m");
		}
		(*k)++;
	}
}

void	print(t_ls *lsls)
{
	int		k;
	t_ls	*ls;
	t_dir	*tmp_dir;
	t_lst	*tmp_lst;
	int		count;

	ls = lsls;
	tmp_dir = ls->d;
	tmp_lst = ls->d->files;
	k = (ls->d->next) ? 1 : 0;
	while (ls->d && ls->d->dir_name)
	{
		count = 0;
		if (k)
			ft_printf("%s:\n", ls->d->str_name);
		if (ls->l_flag)
			ft_printf("total %ld\n", ls->d->block_size);
		tmp_lst = ls->d->files;
		while (ls->d->files)
		{
			print_info(ls, ls->d->files, ls->d, &count);
			ls->d->files = ls->d->files->next;
		}
		if ((ls->col_flag) && (--count % ls->col_flag != ls->col_flag - 1))
			ft_putchar('\n');
		ls->d->files = tmp_lst;
		clear_dir(ls->d);
		ls->d = ls->d->next;
		if (ls->d)
			ft_putchar('\n');
	}
	ls->d = tmp_dir;
	ls->d->files = tmp_lst;
}
