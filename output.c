#include "ft_ls.h"

void	print_type(char type)
{
	if (type == DT_BLK)
		ft_putchar('b');
	else if (type == DT_CHR)
		ft_putchar('c');
	else if (type == DT_DIR)
		ft_putchar('d');
	else if (type == DT_FIFO)
		ft_putchar('p');
	else if (type == DT_LNK)
		ft_putchar('l');
	else if (type == DT_REG)
		ft_putchar('-');
	else if (type == DT_SOCK)
		ft_putchar('s');
}

void	print(t_ls *ls)
{
	int k;

	k = (ls->d->next) ? 1 : 0;
	while (ls->d && ls->d->dir_name)
	{
		if (k)
			ft_printf("%s:\n", ls->d->str_name);
		if (ls->l_flag)
			ft_printf("total %ld\n", ls->d->block_size);
		while (ls->d->files)
		{
			if (ls->d->files->name[0] != '.' || (ls->a_flag))
			{
				if (ls->l_flag)
				{
					int tmp_arg = (ls->d->files->rights[9]) > 0 ? 2 : 3;

					print_type(ls->d->files->type);
					ft_printf("%s %*ld %s  %s%*lld %s ", ls->d->files->rights, tmp_arg, ls->d->files->links,
						ls->d->files->pw_name, ls->d->files->gr_name, ls->d->digits_max + 2, ls->d->files->size, ls->d->files->time);
				}
				ft_printf("%s\n", ls->d->files->name);
			}
			ls->d->files = ls->d->files->next;
		}
		ls->d = ls->d->next;
		if (ls->d)
			ft_printf("\n");
		// closedir(ls.d);
	}
}
