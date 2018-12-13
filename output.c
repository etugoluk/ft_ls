#include "ft_ls.h"

void	print_type(t_lst* f)
{
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
}

void	print_info(t_ls *ls, t_lst* f, int width)
{
	if (f->name[0] != '.' || (ls->a_flag))
	{
		if (ls->l_flag)
		{
			int tmp_arg = (f->rights[9]) > 0 ? 2 : 3;

			print_type(f);
			ft_printf("%s %*ld %s  %s%*lld %s ", f->rights, tmp_arg, f->links,
				f->pw_name, f->gr_name, width, f->size, f->time);
		}
		ft_printf("\033%s%s\n\033[0m", f->color, f->name);
	}
}

void	print(t_ls *lsls)
{
	int k;

	t_ls *ls = lsls;
	t_dir *tmp_dir = ls->d;
	t_lst *tmp_lst = ls->d->files;

	k = (ls->d->next) ? 1 : 0;

	while (ls->d && ls->d->dir_name)
	{
		if (k)
			ft_printf("%s:\n", ls->d->str_name);
		if (ls->l_flag)
			ft_printf("total %ld\n", ls->d->block_size);
		tmp_lst = ls->d->files;
		while (ls->d->files)
		{
			print_info(ls, ls->d->files, ls->d->digits_max + 2);
			ls->d->files = ls->d->files->next;
		}
		ls->d->files = tmp_lst;
		ls->d = ls->d->next;
		if (ls->d)
			ft_printf("\n");
		// closedir(ls.d);
	}
	ls->d = tmp_dir;
	ls->d->files = tmp_lst;
}
